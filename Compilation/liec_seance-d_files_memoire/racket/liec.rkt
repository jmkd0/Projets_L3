#lang racket/base

(require "parser.rkt"
         "analyzer.rkt"
         "simplifier.rkt"
         "compiler.rkt"
         "mips-printer.rkt"
         "helper.rkt")

(define argv (current-command-line-arguments))
(cond
  [(= (vector-length argv) 1)
   (let* ([src (open-input-file (vector-ref argv 0))]
          [prs (parse src)]
          [ast (analyze prs)]
          [smp (simplify ast)]
          [asm (compile smp)])
     (close-input-port src)
     (with-output-to-file (string-append (vector-ref argv 0) ".asm")
       (lambda () (mips-print asm))))]
  [else
   (eprintf "Usage: racket liec.rkt <file>.\n")
   (exit 1)])
