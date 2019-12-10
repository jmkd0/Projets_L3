#lang racket/base

(require racket/match
         "ast.rkt"
         "baselib.rkt"
         "helper.rkt")

(provide analyze)

(define (analyze-expr expr env)
  (match expr
    [(Pnum n pos)
     (cons (Num n)
           'num)]
    [(Pcall f as pos)
     (let ([ft (hash-ref env f
                         (lambda ()
                           (err (format "undefined function '~a'" f) pos)))])
       (unless (Fun? ft)
         (err (format "value '~a' is not a function" f) pos))
       (unless (= (length as) (length (Fun-args ft)))
         (err (format "function '~a' expects ~a arguments but was given ~a"
                      f (length (Fun-args ft) (length as))) pos))
       (let ([aas (map (lambda (a at)
                         (let ([aa (analyze-expr a env)])
                           (unless (eq? at (cdr aa))
                             (errt at (cdr aa) pos))
                           (car aa)))
                       as (Fun-args ft))])
         (cons (Call f aas)
               (Fun-ret ft))))]))

(define (analyze-prog prog env)
  (analyze-expr prog env))

(define (analyze ast)
  (car (analyze-prog ast *baselib-types*)))
