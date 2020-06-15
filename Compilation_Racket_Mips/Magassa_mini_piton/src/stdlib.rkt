#lang racket/base

(require "ast.rkt")

(provide (all-defined-out))

;;; Types of the functions in the standard library
(define *stdlib-types*
  (make-immutable-hash
   (list
    (cons 'cons  (Fun (Lst Any) (list Any (Lst Any))))
    (cons 'hd    (Fun Any (list (Lst Any))))
    (cons 'tl    (Fun (Lst Any) (list (Lst Any))))
    (cons 'nullp (Fun Bool (list (Lst Any))))
    
    (cons '+     (Fun Int (list Int Int)))
    (cons '-     (Fun Int (list Int Int)))
    (cons '*     (Fun Int (list Int Int)))
    (cons '/     (Fun Int (list Int Int)))
    (cons '%     (Fun Int (list Int Int)))
    (cons 'zerop (Fun Bool (list Int)))
    
    (cons '== (Fun Bool (list Int Int)))
    (cons '!= (Fun Bool (list Int Int)))
    (cons '>  (Fun Bool (list Int Int)))
    (cons '<  (Fun Bool (list Int Int)))
    (cons '<= (Fun Bool (list Int Int)))
    (cons '>= (Fun Bool (list Int Int)))
    
    (cons '&& (Fun Bool (list Bool Bool)))
    (cons '|| (Fun Bool (list Bool Bool)))
    (cons '!  (Fun Bool (list Bool)))
    
    (cons 'print_num  (Fun Nil (list Int)))
    (cons 'print_bool (Fun Nil (list Bool)))
    (cons 'print_str  (Fun Nil (list Str)))
    (cons 'print_lst  (Fun Nil (list Any)))
    
    (cons 'strcat (Fun Str (list Str Str)))
    (cons 'atoi   (Fun Int (list Str))))))