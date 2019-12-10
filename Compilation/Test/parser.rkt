#lang racket/base
(require parser-tools/yacc
         parser-tools/lex
         "lexer.rkt"
         "ast.rkt"
         "helper.rkt")
(provide parse)

(define ~parse
  (parser
   (src-pos)
   (tokens constants operators)
   (start prog)
   (end Loef)
   (grammar
    (prog
     [(Lnum) (Pnum $1-start-pos)]
     [(Lnum Lplus Lnum)]
   (error (lambda (tok-ok? tok-name tok-value start-pos end-pos)
            (err "Syntax error")))))))
            


   (define( parse src)
     (~parse (lambda () (get-token src))))
