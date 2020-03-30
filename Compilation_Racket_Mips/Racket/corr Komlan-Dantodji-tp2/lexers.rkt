;;EXERCICE 2
#lang racket/base

(require parser-tools/lex
         racket/port
         (prefix-in : parser-tools/lex-sre))


;;Question 1
(define first-lexer
  (lexer
   ((eof)           'fini)
   (whitespace      (first-lexer input-port))
   (any-char   (begin (displayln lexeme)(first-lexer input-port)))))
 
  
;;Question 2
(call-with-input-string "Est-ce que ça marche ?" first-lexer)

;;Question 3
(define second-lexer
  (lexer
   ((eof)           'fini)
   (whitespace      (second-lexer input-port))
   (any-char        lexeme)))
;;Question 4
(define (second-lex in)
  (let loop ((t (second-lexer in)))
    (unless (eq? t 'fini)
      (printf "~a\n" t)
      (loop (second-lexer in)))))

;;Question 5
(call-with-input-string "Est-ce que ça marche ?" second-lex)
;;Question 6
(define argv (current-command-line-arguments))
(cond
  ((= (vector-length argv) 1)
   (call-with-input-file (vector-ref argv 0) second-lex))
  (else
   (eprintf "Usage: racket lexers.rkt \"file\"\n")
   (exit 1)))











