#lang racket/base

(provide (all-defined-out))

(define *stdlib-typing*
  (make-immutable-hash
   '((%and . (2 . 1))
     (%or  . (2 . 1))
     (%xor . (2 . 1))
     (%not . (1 . 1)))))

(define *stdlib-natives*
  (make-immutable-hash
   `((%and . ,(lambda (l)
                (list (and (car l) (cadr l)))))
     (%or  . ,(lambda (l)
                (list (or (car l) (cadr l)))))
     (%xor . ,(lambda (l)
                (list (or (and (car l) (not (cadr l)))
                          (and (not (car l)) (cadr l))))))
     (%not . ,(lambda (l)
                (list (not (car l))))))))
