#lang racket/base
(require parser-tools/lex
          (prefix-in : parser-tools/lex-sre)
          "helper.rkt")
(provide constants operators get-get-token)
(define-tokens constants
  (Lnum))
(define-empty-tokens operators
  (Leof
   ;;ajout addition
   Lplus))

(define get-token
 (lexer-src-pos
 [(whitespace) (return-without-pos (get-token input-port))]
 ["+"   (
 [(:+numeric) (token-Lnum (string->number lexeme))]
 [(eof) (token-Leof)]
 [any-char (err (format "Unrecognized character '~a'" lexeme))]))

