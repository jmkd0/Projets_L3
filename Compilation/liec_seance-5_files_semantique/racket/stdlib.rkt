#lang racket/base

(provide (all-defined-out))

(define *stdlib-typing*
  (make-immutable-hash '((%and . (2 . 1))
                         (%or  . (2 . 1))
                         (%xor . (2 . 1))
                         (%not . (1 . 1)))))
