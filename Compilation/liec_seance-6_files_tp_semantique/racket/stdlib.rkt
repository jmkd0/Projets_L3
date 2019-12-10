#lang racket/base

(provide (all-defined-out))

;; 'bool and 'num are used as base types
(struct Fun (ret args))

(define *types*
  (make-immutable-hash
   (list
    ;; opérations arithmétiques de base
    (cons '%add (Fun 'num (list 'num 'num)))
    (cons '%sub (Fun 'num (list 'num 'num)))
    (cons '%mul (Fun 'num (list 'num 'num)))
    (cons '%div (Fun 'num (list 'num 'num)))
    ;; comparaisons de nombres
    (cons '%eq  (Fun 'bool (list 'num 'num)))
    (cons '%neq (Fun 'bool (list 'num 'num)))
    (cons '%lt  (Fun 'bool (list 'num 'num)))
    (cons '%gt  (Fun 'bool (list 'num 'num)))
    (cons '%lte (Fun 'bool (list 'num 'num)))
    (cons '%gte (Fun 'bool (list 'num 'num))))))
