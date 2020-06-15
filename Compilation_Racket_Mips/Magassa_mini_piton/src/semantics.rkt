#lang racket/base

(require racket/match
         "ast.rkt"
         "stdlib.rkt"
         (only-in parser-tools/lex
                  (position-line posl)
                  (position-col posc)))

(provide liec-check)

;;; Helper functions

;;; User error
(define (err pos msg (expr #f))
  (eprintf "Error: ~a on line ~a col ~a.\n"
           (if expr (format msg expr) msg)
           (posl pos) (posc pos))
  (exit 1))

;;; Failure of our implementation
(define (fail! v)
  (eprintf "Typing failed on ~a\n" v)
  (exit 1))


;;; Formatting type for printing
(define (fmt-type t (p? #f))
  (match t
    ('int "int")
    ('str "str")
    ('bool "bool")
    ('nil "nil")
    ('any "any")
    ((Lst t) (format "~a list" (fmt-type t)))
    ((Fun r a) (format "~a~a <- ~a~a"
                       (if p? "(" "")
                       (fmt-type r)
                       (foldl (lambda (t fmt)
                                (string-append fmt ", " (fmt-type t #t)))
                              (fmt-type (car a) #t)
                              (cdr a))
                       (if p? ")" "")))))

;;; User type error
(define (errt pos expected-type actual-type)
  (err pos (format "expr has type ~a but an expr of type ~a was expected"
                   (fmt-type actual-type) (fmt-type expected-type))))

;;; Verifying type compatibility of t1 and t2
(define (type-compat? t1 t2)
  (match (cons t1 t2)

    ;; identical types are cmpatible
    ((cons t t)
     #t)

    ;; Any is compatible with anything by definition
    ;; Caveat: we lose a lot of precision here
    ((or (cons 'any _)
         (cons _ 'any))
     #t)

    ;; List of t1 is compatible with List of t2 if t1 is compatible with t2
    ((cons (Lst t1) (Lst t2))
     (type-compat? t1 t2))

    ;; The empty list is compatible with any list
    ((or (cons 'nil (Lst _))
         (cons (Lst _) 'nil))
     #t)

    ;; Function types are compatible if their arguments types are compatible
    ;; one-to-one and their return type is compatible
    ((cons (Fun r1 a1) (Fun r2 a2))
     (andmap type-compat? (cons r1 a1) (cons r2 a2)))

    ;; Otherwise types are incompatible.
    (else #f)))


;;; Actual typing

;;; A program is a list of definitions.
;;; Definitions are of type Nil.
;;; At least one definition must be a function named "main" that returns a
;;; number and takes a number and a list of string (argc argv) as arguments.
(define (liec-check prog)
  (let* ((cp (check-exprs prog *stdlib-types* Nil))
         (main (hash-ref (cdr cp) 'main
                         (lambda ()
                           (eprintf "Error: expected a main function.\n")
                           (exit 1)))))
    (if (not (type-compat? main (Fun Int (list Int (Lst Str)))))
        (begin
          (eprintf "Error: int main(argc, argv : int, str list).\n")
          (exit 1))
        (car cp))))

;;; Checking a list a expressions means verifying that each of them is correct
;;; and that the last one is of the expected type.
(define (check-exprs exprs env expected-type)
  (let* ((rev (reverse exprs)) ;; the list of expressions in reverse order
         (last-expr (car rev)) ;; the last expression (first of rev)
         (exprs (reverse (cdr rev))) ;; all but the last expressions in order

         ;; checking all but the last expressions
         (ce (foldl ;; for each of these expressions
              ;; expr is the current expression
              ;; acc is a pair of 1- the list of already checked expressions
              ;; 2- the current environment updated with the last checked expr
              (lambda (expr acc)
                ;; Check it with the current environment, no care for its type
                (let ((ce (check-expr expr (cdr acc) Any)))
                  ;; build the next value of acc
                  (cons (append (car acc) (list (car ce)))
                        (cdr ce))))

              (cons '() env) ;; initial value for acc
              exprs)) ;; all but the last expressions

         ;; now check the last expression in the current env and expect it to
         ;; be of the expected type of the block / list of expression.
         (l (check-expr last-expr (cdr ce) Any)))

      ;; return the block with always the same format : a pair of 1- the list of
      ;; checked expression and 2- the current environment
      (cons (append (car ce) (list (car l)))
            (cdr l))))


;;; Checking a single expression
;;; Return format is always a pair of :
;;; 1- the internal AST representation and 2- the updated environement
;;;
;;; I believe the code is pretty self-explainatory
(define (check-expr expr env expected-type)
  (match expr
    ((Pvardef id expr type sp)
     (if (hash-has-key? env id)
         (err sp "~a: duplicate definition" id)
         (if (not (type-compat? expected-type Nil))
             (errt sp expected-type Nil)
             (let ((expr (check-expr expr env type)))
               (cons (Let id (car expr))
                     (hash-set env id type))))))

    ((Pvar id expr sp)
      (let ((t (hash-ref env id (lambda ()
                                  (err sp "~a: unbound identifier" id)))))
        (if (not (type-compat? expected-type t))
            (errt sp expected-type t)
            (let ((expr (check-expr expr env t)))
               (cons (Let id (car expr))
                     (hash-set env id t))))))


    ((Pfundef rec? id args body type sp)
     (if (hash-has-key? env id)
         (err sp "~a: duplicate definition" id)
         (let ((args (check-dup-arg (if rec? (cons (Pident id #f) args) args)))
               (args-types (if rec? (cons type (Fun-args type)) (Fun-args type))))
           (if (not (= (length args) (length args-types)))
               (err sp "~a: function arity and type do not match" id)
               (if (not (type-compat? Nil expected-type))
                   (errt sp expected-type Nil)
                   (let ((expr (check-expr body (for/fold ((e env)) ;;; initial value of e is env
                                                          ((a args)        ;;; for each a in args
                                                           (t args-types)) ;;; and t in args-types
                                                  (hash-set e a t)) ;;; add a binding from a to t
                                           (Fun-ret type))))
                           ;; #f because we don't know the lexical environement yet
                     (cons (Func id (Closure rec? (if rec? (cdr args) args) (car expr) #f))
                           (hash-set env id type))))))))


    ((Pcond test yes no sp)
     (let ((t (check-expr test env Bool))
           (y (check-expr yes env expected-type))
           (n (check-expr no env expected-type)))
       (cons (Cond (car t) (car y) (car n))
             env)))

    ((Ploop test body sp)
     (let ((ti (check-expr test env Bool))
           (b  (check-expr body env expected-type)))
       (cons (Loop (car ti) (car b))
             env)))

    ((Pident id sp)
     (let ((t (hash-ref env id (lambda ()
                                 (err sp "~a: unbound identifier" id)))))
       (if (not (type-compat? expected-type t))
           (errt sp expected-type t)
           (cons (Var id) env))))

    ((Pcall id args sp)
     (let ((ft (hash-ref env id (lambda ()
                                  (err sp "~a: unbound identifier" id)))))
       (if (not (= (length args) (length (Fun-args ft))))
           (err sp "~a: arity mismatch" id)
           (if (not (type-compat? expected-type (Fun-ret ft)))
               (errt sp expected-type (Fun-ret ft))
               (cons (Call id (map (lambda (a t) (car (check-expr a env t)))
                                   args (Fun-args ft)))
                     env)))))

    ((Pblock exprs sp)
     (cons (Block (car (check-exprs exprs env Any)))
           env))

    ((Pfunblock exprs ret sp)
     (let ((e (car (check-exprs exprs env Any)))
           (r (car (check-expr ret env expected-type))))
       (cons (Funblock e r)
             env)))

    ((Pconst type value sp)
     (if (not (type-compat? expected-type type))
         (errt sp expected-type type)
         (cons (Const value)
               env)))

    (else (fail! expr))))

;;; Check if a function has multiple arguments with the same name
(define (check-dup-arg args (acc '()))
  (if (null? args)
      (reverse acc)
      (let ((arg (car args)))
        (if (member (Pident-id arg) acc)
            (err (Pident-pos arg)
                 "~a: duplicate function argument"
                 (Pident-id arg))
            (check-dup-arg (cdr args) (cons (Pident-id arg) acc))))))
