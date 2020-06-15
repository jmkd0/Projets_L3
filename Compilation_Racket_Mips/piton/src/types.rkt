#lang racket/base

(require racket/match)
(provide (all-defined-out))

;; None
(define none 'none)
;; Integer
(define int 'int)
;; Boolean
(define bool 'bool)
;; String
(define str 'str)
;; Function
(struct func (return-type params-types) #:transparent)
