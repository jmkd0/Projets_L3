#lang racket/base

(require parser-tools/lex
         (prefix-in : parser-tools/lex-sre))

(provide get-token)

;; Fonction "get-token" écrite avec lex

(define get-token
  (lexer
   ((eof)           'Eof)
   (whitespace      (get-token input-port))
   ("&&"            'And)
   ("||"            'Or)
   ("!"             'Not)
   ("("             'Opar)
   (")"             'Cpar)
   ("="             'Assign)
   (";"             'Semicol)
   ((:+ alphabetic) lexeme)
   (any-char        'Error)))
