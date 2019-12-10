#lang racket
(require parser-tools/lex)

(define (string->char s)
  (car (string->list s)))

(define lex
  (lexer
    ; skip spaces:
    [#\space     (lex input-port)]
    
    ; skip newline:
    [#\newline   (lex input-port)]
   
    ; an actual character:
    [any-char    (list 'CHAR (string->char lexeme))]))