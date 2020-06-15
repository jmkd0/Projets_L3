#lang racket

(require "parser.rkt"
         "semantics.rkt"
         "compiler-mips.rkt"
         "stdlib.rkt"
         "mips.rkt"
         "ast.rkt"
         "parser.rkt"
         "stdlib.rkt")

;;; Analyses du programme et compilation de ce dernier
;;; A mettre dans un autre fichier
(define argv (current-command-line-arguments))
(cond
  ((>= (vector-length argv) 1)
   (define in (open-input-file (vector-ref argv 0)))
   (port-count-lines! in)
   (define parsed (liec-parser in))
   (close-input-port in)
   (define prog (liec-check parsed))

   (for-each mips-emit
          (append
            ;; On initialise notre environnement local :
            (list (Move 'fp 'sp))

            ;; On compile notre programme :
            (first (comp (Block prog)
                 ;; avec un environnement vide :
                 (make-immutable-hash)
                 ;; et fp-sp = 0 (vu que fp = sp à ce moment là) :
                 0))

           ;; On affiche le résultat, qui est dans v0
           (list (Move 't5 'v0)
                 (Li 'v0 1)
                 (Move 'a0 't5)
                 (Syscall)
                 (Li 'v0 0)
                 (Jr 'ra)))))  
  (else
   (eprintf "Usage: racket liec.rkt <source.liec>\n")
   (exit 1)))