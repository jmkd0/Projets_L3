#lang racket/base

(require racket/match
         racket/list
         (prefix-in ast- "ast.rkt"))
(provide simplify-calls)

;; Simplify functions calls in <ast>
;; Replace nested calls by consecutive declarations of values returned by calls
;; ex:
;; print(fact(abs(-8)))
;; becomes:
;; a: int = abs(-8)
;; b: int = fact(a)
;; c: int = print(b)
;; <return> ast
(define (simplify-calls ast)
  (simplify-stmts ast))

;; Group of statement
;; <return> statements
(define (simplify-stmts stmts)
  (apply append (for/list ([stmt stmts])
                  (simplify-stmt stmt))))

;; Statement
;; <return> statements
(define (simplify-stmt stmt)
  (match stmt
    ; variable declaration: val may contain calls
    [(ast-decl id type val)
     (simplify-decl id type val)]
    ; assignation: val may contain calls
    [(ast-assign target val)
     (simplify-assign target val)]
    ; return: val may contain calls
    [(ast-return val)
     (simplify-return val)]
    ; if: test and bodies may contain calls
    [(ast-if test body else-body)
     (simplify-if test body else-body)]
    ; while: test and bodies may contain calls
    [(ast-while test body)
     (simplify-while test body)]
    ; function definition: body may contain calls
    [(ast-funcdef id return-type params body)
     (simplify-funcdef id return-type params body)]
    ; anything else is an expression
    [_ (let-values ([(stmts stmt) (simplify-expr stmt)])
         (append stmts (list stmt)))]))

;; Declaration
;; <return> statements
(define (simplify-decl id type val)
  (let-values ([(stmts val) (simplify-expr val)])
    (append stmts
            (list (ast-decl id type val)))))

;; Assignation
;; <return> statements
(define (simplify-assign target val)
  (let-values ([(stmts val) (simplify-expr val)])
    (append stmts
            (list (ast-assign target val)))))

;; Return
;; <return> statements
(define (simplify-return val)
  (let-values ([(stmts val) (simplify-expr val)])
    (append stmts
            (list (ast-return val)))))

;; If
;; <return> statements
(define (simplify-if test body else-body)
  ; simplify calls in both bodies
  (let ([body (simplify-stmts body)]
        [else-body (if else-body (simplify-stmts else-body) #f)])
    ; and simplify test
    (let-values ([(stmts test) (simplify-expr test)])
      ; put simplified test in new block
      (define test-return (ast-return test))
      (define test-block (ast-block (append stmts
                                            (list test-return))))
      (list (ast-if test-block body else-body)))))

;; While
;; <return> statements
(define (simplify-while test body)
  ; simplify calls in body
  (let ([body (simplify-stmts body)])
    ; and simplify test
    (let-values ([(stmts test) (simplify-expr test)])
      ; put simplified test in new block
      (define test-return (ast-return test))
      (define test-block (ast-block (append stmts
                                            (list test-return))))
      (append empty
              (list (ast-while test-block body))))))

;; Function definition
;; <return> statements
(define (simplify-funcdef id return-type params body)
  ; simplify calls in body
  (let ([body (simplify-stmts body)])
    (list (ast-funcdef id return-type params body))))

(define (expr-is-simple? expr)
  (match expr
    [(? ast-call?) #f]
    ; after typechecking, calls are the only exprs that may contain other calls
    ; (operations and subscript accesses have been transformed into calls)
    ; all other expressions are atomic
    [_ #t]))

;; Expression
;; <return> additional statements, simplified expr
(define (simplify-expr expr)
  (match expr
    [(ast-call callee args) (simplify-call callee args)]
    [_ (values empty
               expr)]))

;; Call
;; <return> additional statements, simplified call
(define (simplify-call callee args)
  (let-values ([(stmts args) (simplify-args args)])
    (values stmts
            (ast-call callee args))))

;; Call arguments
;; <return> additional statements, simplified args
(define (simplify-args args)
  (for/fold ([stmts (list)]
             [args (list)])
            ([arg args])
    (if (expr-is-simple? arg)
        ; keep argument as it is if already simple
        (values stmts
                (append args (list arg)))
        (let-values ([(additional-stmts name) (simplify-arg arg)])
          (let ([stmts (append stmts additional-stmts)]
                [args (append args (list name))])
            (values stmts
                    args))))))

;; Call argument
;; <return> statements, name replacing <arg>
(define (simplify-arg arg)
  (define id (string-append "auto_" (symbol->string (gensym))))
  ; new variable declaration with no type (ok because typechecking is already done)
  ; argument is assigned to the variable
  ; NB: calling simplify-stmt to simplify all calls recursively
  (define stmts (simplify-stmt (ast-decl id #f arg)))
  (values stmts
          (ast-name id)))
