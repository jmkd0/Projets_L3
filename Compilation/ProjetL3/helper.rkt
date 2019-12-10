#lang racket/base
(require racket/match
         racket/string
         (only-in parser-tools/lex position-line position-col)
         "ast.rkt")

(provide error)
(define (error massage pos)
    (eprintf "Error on line ~a colon ~a: ~a.\n"
    (position-line pos)
    (position-col pos)
    massage)
 (exit 1))