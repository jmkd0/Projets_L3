#lang racket/base

(require racket/match
         "stdlib.rkt"
         "ast.rkt")

(provide gawi-eval)

(define (fail! msg)
  (eprintf "fatal error: ~a\n" msg)
  (exit 1))

(define (gawi-eval prog)
  (eval-prog prog *stdlib-natives*))

(define (eval-prog prog benv)
  (match prog
    [(list) (fail! "empty program")]
    [(list main)
     (let* ([inputs (map (lambda (i)
                           (printf "~a? " i)
                           (Bit (eq? (read) 1)))
                         (Block-inputs main))]
            [outputs (eval-block main inputs (make-immutable-hash) benv)])
       (displayln "…")
       (for-each (lambda (o v) (printf "~a: ~a\n" o (if v 1 0)))
                 (Block-outputs main) outputs))]
    [(cons b prog)
     (eval-prog prog (hash-set benv (Block-name b) b))]))

(define (eval-block b args venv benv)
  (let* ([inputs (env-add (Block-inputs b) args venv benv)]
         [venv (eval-instrs (Block-body b) inputs benv)])
    (map (lambda (o) (hash-ref venv o)) (Block-outputs b))))

(define (eval-instrs instrs venv benv)
  (match instrs
    [(list) venv]
    [(cons a instrs)
     (let ([venv (env-add (Assign-outputs a) (list (Assign-expr a)) venv benv)])
       (eval-instrs instrs venv benv))]))

(define (eval-expr expr venv benv)
  (match expr
    [(Bit b) (list b)]
    [(Var v) (list (hash-ref venv v))]
    [(Call b a)
     (match (hash-ref benv b)
       [(? Block? b) (eval-block b a venv benv)]
       [(? procedure? f) (f (eval-args a venv benv))]
       [else (fail! "not a callable")])]
    [else (fail! "not an expression"))]))

(define (eval-args args venv benv)
  (apply append (map (lambda (a) (eval-expr a venv benv)) args)))

(define (env-add names exprs venv benv)
  (let ([val (eval-args exprs venv benv)])
    (foldl (lambda (n v e) (hash-set e n v)) venv names val)))
