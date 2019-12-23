#lang racket/base

(provide get-token)

;; Fonction "get-token" écrite sous forme d'automate

(define buf "")

(define nb-states 13)

(define final (make-vector (+ nb-states 1) null))

(vector-set! final 3  (cons #t 'Not))
(vector-set! final 4  (cons #t 'Assign))
(vector-set! final 5  (cons #t 'Semicol))
(vector-set! final 6  (cons #t 'And))
(vector-set! final 7  (cons #t 'Or))
(vector-set! final 8  (cons #t 'Opar))
(vector-set! final 9  (cons #t 'Cpar))
(vector-set! final 11 (cons #f 'Var))
(vector-set! final 13 (cons #t 'Error))

(define transitions (make-vector nb-states null))

(define (state n) (vector-ref transitions n))

(vector-set! transitions 0 (make-vector 256 nb-states))
(vector-set! (state 0) (char->integer #\space) 0)
(vector-set! (state 0) (char->integer #\newline) 0)
(vector-set! (state 0) (char->integer #\tab) 0)
(vector-set! (state 0) (char->integer #\&) 1)
(vector-set! (state 0) (char->integer #\|) 2)
(vector-set! (state 0) (char->integer #\!) 3)
(vector-set! (state 0) (char->integer #\=) 4)
(vector-set! (state 0) (char->integer #\;) 5)
(vector-set! (state 0) (char->integer #\() 8)
(vector-set! (state 0) (char->integer #\)) 9)

(vector-set! transitions 1 (make-vector 256 nb-states))
(vector-set! (state 1) (char->integer #\&) 6)

(vector-set! transitions 2 (make-vector 256 nb-states))
(vector-set! (state 2) (char->integer #\|) 7)

(vector-set! transitions 10 (make-vector 256 11))

(let loop ((c (char->integer #\a)))
  (vector-set! (state 0) c 10)
  (vector-set! (state 10) c 10)
  (unless (eq? c (char->integer #\z))
    (loop (add1 c))))

(define (peek-c in)
  (let ((c (peek-char in)))
    (if (eof-object? c)
        0
        (char->integer c))))

(define (get-token in)
  (if (eof-object? (peek-char in))
      'Eof
      (let automaton ((s 0))
        (let* ((c (peek-c in))
               (ns (vector-ref (state s) c))
               (f (vector-ref final ns)))
          (if (null? f)
              (begin ;; pas final
                (if (= ns s) ;; si même état
                    (set! buf (string-append buf (string (read-char in)))) ;; on bufferise
                    (begin
                      (set! buf (string (integer->char c))) ;; on reset le buffer au c courant
                      (read-char in))) ;; et on consomme
                (automaton ns)) ;; on continue
              (begin ;; final
                (if (car f)
                    (begin
                      (read-char in) ;; on consomme si besoin
                      (cdr f)) ;; on renvoie le token
                    buf))))))) ;; on renvoie la valeur
