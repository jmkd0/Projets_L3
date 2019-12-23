#lang racket/base

(require "lexer.rkt"
         "parser.rkt"
         "semantics.rkt")

(define argv (current-command-line-arguments))
(cond
  [(= (vector-length argv) 1)
   (define src (open-input-file (vector-ref argv 0)))
   (port-count-lines! src)
   (define parsed (parse (lambda () (tokenize src))))
   (close-input-port src)
   (printf "Program syntaxiquement valide")
   (define ast (analyze parsed))
   (displayln ast)]
  [else
   (eprintf "Usage: racket arith.rkt <file>\n")
   (exit 1)])
