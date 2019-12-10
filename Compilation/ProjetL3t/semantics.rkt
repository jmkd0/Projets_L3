#lang racket/base

(require racket/match
         racket/set
         (only-in parser-tools/lex position-line position-col)
         "ast.rkt"
         "stdlib.rkt")

(provide gawi-analyze)

(define (fail! msg)
  (eprintf "Fatal error: ~a.\n" msg)
  (exit 1))

(define (err msg pos)
  (eprintf "Error on line ~a col ~a: ~a.\n"
           (position-line pos)
           (position-col pos)
           msg)
  (exit 1))

(define (warn msg pos)
  (eprintf "Warning on line ~a col ~a: ~a.\n"
           (position-line pos)
           (position-col pos)
           msg))

(define (~be n) (if (= n 1) "is" "are"))
(define (~s n) (if (= n 1) "" "s"))

(define (analyze-prog prog env)
  ;; analyse d'un programme :
  ;; on parcours la liste des block et on analyse chaque block
  ;; on passe chaque fois l'environnement retourné par l'analyse du block précédent
  ;; et reconstruit la liste avec le résultat de l'analyse au fur et à mesure
  (match prog
    [(list) (fail! "this should not happen")]
    [(list last-block)
     (unless (eq? (Pblock-name last-block) 'main)
       (err "missing 'main' block" (Pblock-pos last-block)))
     (list (car (analyze-block last-block env)))]
    [(cons block prog)
     (let ([ab (analyze-block block env)])
       (cons (car ab)
             (analyze-prog prog (cdr ab))))]))

(define (analyze-block block env)
  ;; analyse d'un block :
  ;; on analyse chaque instruction de son body de la même façon que les block d'un programme
  ;; et à la fin
  ;; - on vérifie aussi que les sorties sont bien écrites
  ;; - on alerte si les entrées sont inutilisées
  (let ([inputs (Pblock-inputs block)]
        [outputs (Pblock-outputs block)])
    (define body
      (let analyze-body ([body (Pblock-body block)]
                         [lenv (cons (list->set inputs) (set))])
        (match body
          [(list)
           (begin
             (let ([written (car lenv)]
                   [outs (list->set outputs)]
                   [read (cdr lenv)]
                   [ins (list->set inputs)])
               (unless (subset? outs written)
                 (err (format "output~a ~a are not written to in block ~a"
                              (~s (set-count (set-subtract outs written)))
                              (set->list (set-subtract outs written))
                              (Pblock-name block))
                      (Pblock-pos block)))
               (unless (subset? ins read)
                 (warn (format "unused input~a ~a in block ~a"
                               (~s (set-count (set-subtract ins read)))
                               (set->list (set-subtract ins read))
                               (Pblock-name block))
                       (Pblock-pos block))))
             null)]
          [(cons instr body)
           (let ([ai (analyze-instr instr env lenv)])
             (cons (car ai)
                   (analyze-body body (cdr ai))))])))
    (cons
     (Block (Pblock-name block) inputs outputs body)
     (hash-set env (Pblock-name block) (cons (length inputs) (length outputs))))))

(define (analyze-instr instr env lenv)
  ;; analyse d'une instruction :
  ;; on vérifie l'arité de l'affectation
  (let ([ae (analyze-expr (Passign-expr instr) env lenv)]
        [nb-outputs (length (Passign-outputs instr))])
    (unless (= nb-outputs (cdr ae))
      (err (format "assignment expects ~a output~a but ~a ~a given"
                   nb-outputs (~s nb-outputs)
                   (cdr ae) (~be (cdr ae)))
           (Passign-pos instr)))
    (cons (Assign (Passign-outputs instr) (car ae))
          (cons (set-union (car lenv)
                           (list->set (Passign-outputs instr)))
                (set-union (cdr lenv)
                           (collect-read-var (car ae)))))))

(define (analyze-expr expr env lenv)
  ;; analyse d'une expression :
  ;; on utilise match pour agir en fonction du type d'expression
  (match expr
    [(Pcall block args pos)
     (let ([block-arity
            (hash-ref env block (lambda () (err (format "unknown block ~a" block) pos)))]
           [aas (map (lambda (a) (analyze-expr a env lenv)) args)])
       (let ([nb-inputs (apply + (map cdr aas))])
         (unless (= nb-inputs (car block-arity))
           (err (format "block ~a expects ~a input~a but ~a ~a given"
                        block
                        (car block-arity) (~s (car block-arity))
                        nb-inputs (~be nb-inputs))
                pos)))
       (cons (Call block (map car aas))
             (cdr block-arity)))]
    [(Pident name pos)
     (if (set-member? (car lenv) name)
         (cons (Var name) 1)
         (err (format "unknown variable ~a" name) pos))]
    [(Pbit val pos)
     (cons (Bit val) 1)]))

(define (collect-read-var expr)
  ;; renvoie l'ensemble des variables lues par une expression
  (match expr
    [(Call _ args) (apply set-union (map collect-read-var args))]
    [(Var name) (set name)]
    [(Bit _) (set)]))

(define (gawi-analyze parsed)
  (analyze-prog parsed *stdlib-typing*))
