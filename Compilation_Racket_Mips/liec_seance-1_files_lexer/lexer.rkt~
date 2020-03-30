#lang racket/base

(require parser-tools/lex
         (prefix-in : parser-tools/lex-sre))

(provide get-token)

(define-empty-tokens operators
  (Eof
   And Or Not
   Opar Cpar
   Assign Semicol))

(define-tokens identifiers
  (Var))

(define get-token
  (lexer
   ((eof)           (token-Eof))
   (whitespace      (get-token input-port))
   ("&&"            (token-And))
   ("||"            (token-Or))
   ("!"             (token-Not))
   ("("             (token-Opar))
   (")"             (token-Cpar))
   ("="             (token-Assign))
   (";"             (token-Semicol))
   ((:+ alphabetic) (token-Var lexeme))
   (any-char        (error (format "Unrecognized char '~a' at offset ~a."
                                   lexeme (position-offset start-pos))))))
