#lang racket/base

(require parser-tools/lex
         (prefix-in : parser-tools/lex-sre)
         "helper.rkt")

(provide constants operators get-token)

(define-tokens constants
  (Lnum Lstr Lident))

(define-empty-tokens operators
  (Leof
   Lplus
   Lopar Lcpar Lcomma))

(define get-token
  (lexer-src-pos
   [(eof)        (token-Leof)]
   [whitespace   (return-without-pos (get-token input-port))]
   ["+"          (token-Lplus)]
   ["("          (token-Lopar)]
   [")"          (token-Lcpar)]
   [","          (token-Lcomma)]
   ["print_num"  (token-Lident (string->symbol lexeme))]
   ["print_str"  (token-Lident (string->symbol lexeme))]
   ["pair"       (token-Lident (string->symbol lexeme))]
   ["head"       (token-Lident (string->symbol lexeme))]
   ["tail"       (token-Lident (string->symbol lexeme))]
   [(:+ numeric) (token-Lnum (string->number lexeme))]
   ["\""         (token-Lstr (read-str input-port))]
   [any-char (err (format "unrecognized character '~a'" lexeme)
                  start-pos)]))

(define read-str
  (lexer
   ["\\\""   (string-append "\"" (read-str input-port))]
   ["\""     ""]
   [any-char (string-append lexeme (read-str input-port))]))
