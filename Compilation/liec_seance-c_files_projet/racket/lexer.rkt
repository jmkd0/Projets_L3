#lang racket/base

(require parser-tools/lex
         (prefix-in : parser-tools/lex-sre)
         "helper.rkt")

(provide constants operators get-token)

(define-tokens constants
  (Lnum))

(define-empty-tokens operators
  (Leof
   Lplus))

(define get-token
  (lexer-src-pos
   [(eof)        (token-Leof)]
   [whitespace   (return-without-pos (get-token input-port))]
   ["+"          (token-Lplus)]
   [(:+ numeric) (token-Lnum (string->number lexeme))]
   [any-char (err (format "unrecognized character '~a'" lexeme)
                  start-pos)]))
