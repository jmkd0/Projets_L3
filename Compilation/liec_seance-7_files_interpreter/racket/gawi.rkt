#lang racket/base

(require "parser.rkt"
         "semantics.rkt"
         "eval.rkt")

(define argv (current-command-line-arguments))
(cond
  [(= (vector-length argv) 1)
   (define src (open-input-file (vector-ref argv 0)))
   (port-count-lines! src)
   (define parsed (gawi-parser src))
   (close-input-port src)
   (define ast (gawi-analyze parsed))
   (gawi-eval ast)]
  [else
   (eprintf "Usage: racket gawi.rkt <file>\n")
   (exit 1)])
