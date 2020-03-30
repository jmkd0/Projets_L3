#lang racket/base

(require racket/match
         racket/string
         (only-in parser-tools/lex position-line position-col)
         "ast.rkt")

(provide err errt)

(define (err msg pos)
  (eprintf "Error on line ~a col ~a: ~a.\n"
           (position-line pos)
           (position-col pos)
           msg)
  (exit 1))

(define (type->string t)
  (match t
    ['num  "number"]
    [(Fun r a)
     (string-append (if (> (length a) 1) "(" "")
                    (string-join (map type->string a) ", ")
                    (if (> (length a) 1) ")" "")
                    " -> " (type->string r))]))

(define (errt expected given pos)
  (err (format "expected ~a but given ~a"
               (type->string expected)
               (type->string given))
       pos))
