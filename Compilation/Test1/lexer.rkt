#lang racket/base

(require parser-tools/lex
          (prefix-in : parser-tools/lex-sre))
(provide constants operators get-get-token)
(define-tokens constants
  (Lnum))
(define-empty-tokens operators
  (Leof))
(define get-token
  (lexer-src-pos
  [(whitespace) (return-without-pos (get-token input-port))]
  [(:+numeric) (token-Lnum (string->number lexeme))]
  [(eof) (token-Loef)]
  [any-char (erreur (format "Charactere '~a' non reconnue" lexeme))]))


(define (erreur message)
  (eprintf "Erreur: ~a.\n" message)
  (exit 1))