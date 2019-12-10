#lang racket/base

(require racket/match
         "ast.rkt")

(provide simplify)

(define (collect-constant-strings ast)
  (define uniq 0)
  (define (ccs ast)
    (match ast
      [(Nil)
       (cons (Nil)
             (list))]
      [(Num n)
       (cons (Num n)
             (list))]
      [(Str s)
       (set! uniq (add1 uniq))
       (let ([lbl (format "str_~a" uniq)])
         (cons (Data lbl)
               (list (cons lbl s))))]
      [(Call f a)
       (let ([as (map ccs a)])
         (cons (Call f (map car as))
               (apply append (map cdr as))))]))
  (ccs ast))

(define (simplify ast)
  (collect-constant-strings ast))
