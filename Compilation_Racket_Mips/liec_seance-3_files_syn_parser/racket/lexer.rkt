#lang racket/base

(require parser-tools/lex
         (prefix-in : parser-tools/lex-sre))

(provide token token-name token-value operators bits)

(define-empty-tokens operators
  (Land Lor Lnot Lopar Lcpar Lend))

(define-tokens bits
  (Lbool))

(define token
  (lexer
   ((eof)      (token-Lend))
   (whitespace (token input-port))
   ("&"        (token-Land))
   ("|"        (token-Lor))
   ("!"        (token-Lnot))
   ("("        (token-Lopar))
   (")"        (token-Lcpar))
   ("0"        (token-Lbool #f))
   ("1"        (token-Lbool))
   (any-char   (error (format "Unrecognized char '~a' at offset ~a."
                              lexeme (position-offset start-pos))))))
