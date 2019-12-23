#lang racket/base

(require (only-in parser-tools/lex position-line position-col)
         racket/match
         racket/string
         "ast.rkt"
         "stdlib.rkt")

(provide analyze)

(define DEBUG #t)

;; fonctions d'aide à la gestion des erreurs

(define (fail! msg)
  (eprintf "Fatal error: ~a.\n" msg)
  (exit 1))

(define (err msg pos)
  (eprintf "Error on line ~a col ~a: ~a.\n"
           (position-line pos)
           (position-col pos)
           msg)
  (exit 1))

(define (type->string t)
  (match t
    ['bool "boolean"]
    ['num  "number"]
    [(Fun r a)
     (string-append (if (> (length a) 1) "(" "")
                    (string-join (map type->string a) ", ")
                    (if (> (length a) 1) ")" "")
                    " -> " (type->string r))]))

(define (expr-pos expr)
  (match expr
    [(Pbool _ pos)     pos]
    [(Pnum _ pos)      pos]
    [(Pvar _ pos)      pos]
    [(Pcall _ _ pos)   pos]
    [(Pcond _ _ _ pos) pos]
    [else (fail! "not an expression")]))

(define (errt expected given pos)
  (err (format "expected ~a but given ~a"
               (type->string expected)
               (type->string given))
       pos))

;; analyse sémantique

(define (analyze parsed)
  (analyze-prog parsed *types*))

(define (analyze-prog prog env)
  (match prog
    [(list)
     (begin
       (when DEBUG
         (hash-for-each env (lambda (v t) (printf "~a: ~a\n" v t))))
       null)]
    [(cons i p)
     (let ([ai (analyze-instr i env)])
       (cons (car ai) (analyze-prog p (cdr ai))))]))

(define (analyze-instr instr env)
  (match instr
    [(Passign v e pos)
     (let ([ae (analyze-expr e env)])
       (cons (Assign v (car ae))
             (hash-set env v (cdr ae))))]
    [else (fail! "not an instruction")]))

(define (analyze-expr expr env)
  (match expr
    [(Pbool b pos)
     (cons (Bool b)
           'bool)]
    [(Pnum n pos)
     (cons (Num n)
           'num)]
    [(Pvar v pos)
     (if (hash-has-key? env v)
         (cons (Var v)
               (hash-ref env v))
         (err (format "unbound variable '~a'" v) pos))]
    [(Pcall f as pos)
     (let ([ft (hash-ref env f)])
       (let ([aas (map (lambda (a t)
                         (let ([aa (analyze-expr a env)])
                           (unless (eq? (cdr aa) t)
                             (errt t (cdr aa) (expr-pos a)))
                           (car aa)))
                       as (Fun-args ft))])
         (cons (Call f aas)
               (Fun-ret ft))))]
    [(Pcond t y n pos)
     (let ([at (analyze-expr t env)]
           [ay (analyze-expr y env)]
           [an (analyze-expr n env)])
       (unless (eq? (cdr at) 'bool)
         (errt 'bool (cdr at) (expr-pos t)))
       (unless (eq? (cdr ay) (cdr an))
         (errt (cdr ay) (cdr an) (expr-pos n)))
       (cons (Cond at ay an)
             (cdr ay)))]
    [else (fail! "not an expression")]))