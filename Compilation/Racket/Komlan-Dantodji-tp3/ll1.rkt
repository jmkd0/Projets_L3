#lang racket/base
;;Exercice 2
(require racket/port
         "lexer.rkt")

(define current-token null)
(define in null)
(define-tokens numbers (NUMBER))

(define (match-t t)
  (cond
    ((eq? t (token-name current-token))
     (set! current-token(token in)
           (else
            (error 'parser "Expected ~a\n" t))))))
(define (match-expr)
  (cond
    (match-num)
    ((match-expr)
     (match-t 'Plus)
     (match-expr))
    ((match-expr)
     (match-t 'Minus)
     (match-expr))
    ((match-expr)
     (match-t 'Star)
     (match-expr))
    ((match-expr)
     (match-t 'Slash)
     (match-expr))
    ((match-t 'Opar)
     (match-expr)
     (match-t 'Cpar))))

(define (match-num)
  (match-t 'Minus)?
  (match-val))

(define (match-val)
  (cond
    ((eq? 'numeric(token-name current-token))
     (set! :+ current-token(token in)))
    (else
     (error 'parser "Expected numeric" ))))



(define argv (current-command-line-arguments))
(cond
  ((= (vector-length argv) 1)
   (set! in (open-input-string (vector-ref argv 0)))
   (set! current-token (token in))
   (match-expr)
   (match-t 'Lend)
   (printf "Programme syntaxiquement valide !\n"))
  (else
   (eprintf "Usage: racket ll1.rkt \"string\"\n")
   (exit 1)))
  
    