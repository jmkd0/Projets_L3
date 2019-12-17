#lang racket/base
(provide err)
(define (err msg)
  (eprintf "Error: ~a.\n" msg)
  (exit 1))
