#lang racket/base

(provide get-token)

;; Fonction "get-token" écrite à la main

(define (get-token in)
  (let ignore ((c (read-char in)))
    (cond
      ((eof-object? c) 'Eof)
      ((char-whitespace? c) (ignore (read-char in)))
      ((char-alphabetic? c)
       (let loop-var ((v (list c))
                      (c (peek-char in)))
         (cond
           ((eof-object? c) (list->string (reverse v)))
           ((char-alphabetic? c) (read-char in)
                                 (loop-var (cons c v) (peek-char in)))
           (else (list->string (reverse v))))))
      ((eq? c #\&)
       (let ((c (peek-char in)))
         (cond
           ((eof-object? c) 'Error)
           ((eq? c #\&) (read-char in) 'And)
           (else 'Error))))
      ((eq? c #\|)
       (let ((c (peek-char in)))
         (cond
           ((eof-object? c) 'Error)
           ((eq? c #\|) (read-char in) 'Or)
           (else 'Error))))
      ((eq? c #\!) 'Not)
      ((eq? c #\() 'Opar)
      ((eq? c #\)) 'Cpar)
      ((eq? c #\=) 'Assign)
      ((eq? c #\;) 'Semicol)
      (else 'Error))))
