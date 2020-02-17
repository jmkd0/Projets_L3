#lang racket/base

(require "parser.rkt"
         "helper.rkt")
(define argv (current-command-line-arguments)
  (cond
    [(= (vector-length argv) 1)
     (define src (open-input-file (vector-ref argv 0)))
     (port-count-line! src)
     ;;(displayln (parse src) ;; pour juste le parser
     ;;interviention de sementic
     (define parsed (parse src))
     (define ast (analyse parsed))
     (define asm (compile ast))
    ;; (displayln ast)   ;; on l'enleve pour utiliser mips
     (mips-emit asm)]
    [else
     (err "Usage: racket liec.rkt <file>")])
