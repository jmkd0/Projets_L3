#lang racket/base

(require "lexer.rkt"
         "parser.rkt"
         "semantic.rkt"
         "compiler.rkt"
         "mips-printer.rkt")

(define argv (current-command-line-arguments))
(cond
  [(= (vector-length argv) 1)
   (define src (open-input-file (vector-ref argv 0)))
   (port-count-lines! src)
   (define parsed (parse src))

   (close-input-port src)
   (printf "Program syntaxiquement valide\n\n")
   (define ast (analyze parsed))
   (displayln ast)
   (printf "Program semantiquement valide\n\n")
   (define asm (compile ast))
   ;;(displayln asm)
   (printf "Program bien compilé\n\n")
   (close-input-port src)
   (with-output-to-file (string-append (vector-ref argv 0) ".asm")
       (lambda () (mips-print asm)))
   ]
  [else
   (eprintf "Usage: racket main.rkt <file>\n")
   (exit 1)])