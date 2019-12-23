;;EXERCICE 3
#lang racket/base
(require parser-tools/lex
         racket/port
         (prefix-in : parser-tools/lex-sre))

;(provide first-lexer)
(define-empty-tokens symbols
  (PLUS MINUS START SLASH OPAR CPAR))

(define-tokens numbers (NUMBER))
 
;;Question 3
(define tokenize
  (lexer
   ((eof)           'END)
   (whitespace      (tokenize input-port))
   ("+"              'token-PLUS)
   ("-"              'token-MINUS)
   ("*"              'token-START)
   ("/"              'token-SLASH)
   ("("              'token-OPAR)
   (")"              'token-CPAR)
   ((:+ numeric)   (token-NUMBER(string->number lexeme)))
   (any-char        (error
                     format "Lexing: Invalid char '~a' on line ~a col ~a."
                     lexeme
                     (position-line start-pos)
                     (position-col start-pos)))))
(define tokenize-pos
  (lexer-src-pos
   ((eof)           'END)
   (whitespace      (return-without-pos(tokenize input-port)))
   ("+"              'token-PLUS)
   ("-"              'token-MINUS)
   ("*"              'token-START)
   ("/"              'token-SLASH)
   ("("              'token-OPAR)
   (")"              'token-CPAR)
   ((:+ numeric)   (token-NUMBER(string->number lexeme)))
   (any-char        (error
                     format "Lexing: Invalid char '~a' on line ~a col ~a."
                     lexeme
                     (position-line start-pos)
                     (position-col start-pos)))))
;;Question 4 et 6
 (define (lex in)
   (port-count-lines! in)
  (let loop ((t (tokenize-pos in)))
    (unless (eq? t 'END)
      (write t)
      (newline) 
      (loop (tokenize in)))))

  (call-with-input-string "124+  56" lex)
;;Question 5
(define argv (current-command-line-arguments))
(cond
  ((= (vector-length argv) 1)
   (call-with-input-file (vector-ref argv 0) lex))
  (else
   (eprintf "Usage: racket arith-lexer.rkt \"file\"\n")
   (exit 1)))