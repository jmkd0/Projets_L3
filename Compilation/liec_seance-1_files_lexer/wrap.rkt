#lang racket/base

(require racket/port
         "lexer.rkt")

(define (lex in)
  (let loop ((t (get-token in)))
    (unless (eq? t 'Eof)
      (write t)
      (newline)
      (loop (get-token in)))))

(define argv (current-command-line-arguments))
(cond
  ((= (vector-length argv) 1)
   (call-with-input-string (vector-ref argv 0) lex))
  (else
   (eprintf "Usage: racket lexer.rkt \"string\"\n")
   (exit 1)))
