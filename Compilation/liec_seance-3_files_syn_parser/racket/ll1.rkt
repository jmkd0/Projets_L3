#lang racket/base

(require racket/port
         "lexer.rkt")

(define current-token null)
(define in null)

;; Non-terminaux

(define (match-expr)
  (match-disj)
  (match-disj-cont))

(define (match-disj)
  (match-conj)
  (match-conj-cont))

(define (match-disj-cont)
  (cond
    ((eq? 'Lor (token-name current-token))
     (match-t 'Lor)
     (match-expr))
    (else
     (match-ε))))

(define (match-conj)
  (cond
    ((eq? 'Lopar (token-name current-token))
     (match-t 'Lopar)
     (match-expr)
     (match-t 'Lcpar))
    ((eq? 'Lnot (token-name current-token))
     (match-t 'Lnot)
     (match-conj))
    (else
     (match-bit))))

(define (match-conj-cont)
  (cond
    ((eq? 'Land (token-name current-token))
     (match-t 'Land)
     (match-expr))
    (else
     (match-ε))))

;; Terminaux

(define (match-bit)
  (cond
    ((eq? 'Lbool (token-name current-token))
     (set! current-token (token in)))
    (else
     (error 'parser "Expected bit value\n"))))

(define (match-t t)
  (cond
    ((eq? t (token-name current-token))
     (set! current-token (token in)))
    (else
     (error 'parser "Expected ~a\n" t))))

(define (match-ε)
  null)

;; Wrapper

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
