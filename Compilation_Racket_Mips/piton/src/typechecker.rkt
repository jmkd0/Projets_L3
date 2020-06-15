#lang racket/base

(require racket/match
         racket/list
         racket/hash
         (prefix-in ast- "ast.rkt")
         (prefix-in std- "types.rkt")
         (prefix-in std- "typed-builtin.rkt")
         "errors.rkt")
(provide typecheck)
(require racket/trace)

;; <returns> ast
(define (typecheck ast)
  ; local and built-in scopes (no global)
  (define symtables (list (hash) std-lib))
  (let-values ([(ast _) (typecheck-stmts ast symtables std-none)])
    ast))

;; <returns> type for id or fails if not declared
(define (resolve-id id pos symtables)
  (when (empty? symtables)
    (raise-undeclared-name-error pos id))
  (define symtable (first symtables))
  (if (hash-has-key? symtable id)
      (hash-ref symtable id)
      (resolve-id id pos (rest symtables))))

;; Group of statements
;; <returns> statements, symtables
(define (typecheck-stmts stmts symtables expected-return-type [allow-funcdef? #t])
  (for/fold ([stmts (list)]
             [symtables symtables])
            ([stmt stmts])
    #:final (ast-pos-return? stmt) ; everything after return is ignored
    (let-values ([(stmt symtables) (typecheck-stmt stmt symtables expected-return-type allow-funcdef?)])
      (values (append stmts (list stmt))
              symtables))))

;; Statement
;; <returns> statement, symtables
(define (typecheck-stmt stmt symtables expected-return-type [allow-funcdef? #t])
  (match stmt
    ; variable declaration
    [(ast-pos-decl id type val pos)
     (typecheck-decl id type val pos symtables)]
    ; assignation
    [(ast-pos-assign target val pos)
     (typecheck-assign target val pos symtables)]
    ; return
    [(ast-pos-return value pos)
     (typecheck-return value pos symtables expected-return-type)]
    ; if
    [(ast-pos-if test body else-body pos)
     (typecheck-if test body else-body pos symtables expected-return-type)]
    ; while
    [(ast-pos-while test body pos)
     (typecheck-while test body pos symtables expected-return-type)]
    ; function definition
    [(ast-pos-funcdef id return-type params body pos)
     (when (not allow-funcdef?)
       (raise-funcdef-not-allowed-error pos))
     (typecheck-funcdef id return-type params body pos symtables)]
    ; anything else is an expression
    [_
     (let-values ([(stmt type) (typecheck-expr stmt symtables)])
       (values stmt
               symtables))]))

;; Variable declaration
;; <returns> statement, symtables
(define (typecheck-decl id type val pos symtables)
  (define local-symtable (first symtables))
  ; check for existing symbol with same id
  (when (hash-has-key? local-symtable id)
    (raise-name-already-declared-error pos id))
  ; typecheck value expression
  (let-values ([(val val-type) (typecheck-expr val symtables)])
    ; check value type matches
    (when (not (equal? type val-type))
      (raise-assign-type-error pos id type val-type))
    ; update local symtable (after value typecheck, to prevent self-assign)
    (let* ([local-symtable (hash-set local-symtable id type)]
           [symtables (cons local-symtable (rest symtables))])
      (values (ast-decl id type val)
              symtables))))

;; Assignation
;; <returns> statement, values
(define (typecheck-assign target val pos symtables)
  ; typecheck value expression
  (define target-type (resolve-id target pos symtables))
  (let-values ([(val val-type) (typecheck-expr val symtables)])
    ; forbid function reassign
    (when (std-func? target-type)
      (raise-assign-func-error pos))
    ; check value type matches
    (when (not (equal? target-type val-type))
      (raise-assign-type-error pos target target-type val-type))
    (values (ast-assign target val)
            symtables)))

;; Return
;; <returns> statement, symtables
(define (typecheck-return val pos symtables expected-return-type)
  ; return without value: default to none
  (let ([val (or val (ast-pos-const 'none pos))])
    ; typecheck value expression
    (let-values ([(val val-type) (typecheck-expr val symtables)])
      ; check value type matches expected return type
      (unless (equal? val-type expected-return-type)
        (raise-return-type-error pos val-type expected-return-type))
      (values (ast-return val)
              symtables))))

;; If
;; <returns> statement, symtables
(define (typecheck-if test body else-body pos symtables expected-return-type)
  ; typecheck test expression
  (let-values ([(test test-type) (typecheck-expr test symtables)])
    ; convert test to bool
    (let ([test
           (match test-type
             [(== std-int)   test]
             [(== std-bool)  test]
             [(== std-str)   (ast-call "str_to_bool" (list test))]
             [(== std-none)  (ast-call "none_to_bool" (list test))]
             [(std-func _ _) (ast-call "func_to_bool" (list test))])])
      ; typecheck body statements
      (let-values ([(body if-symtables) (typecheck-stmts body symtables expected-return-type #f)])
        (if (not else-body)
            (values (ast-if test body else-body)
                    if-symtables)
            ; typecheck else-body statements if present
            (let-values ([(else-body else-symtables) (typecheck-stmts else-body symtables expected-return-type #f)])
              ; merge if/else symtables
              (define merged-symtable (merge-if-else-symtables (first if-symtables)
                                                               (first else-symtables) pos))
              (values (ast-if test body else-body)
                      (cons merged-symtable (rest symtables)))))))))

;; <returns> unique symtable and check type consistency
(define (merge-if-else-symtables if-symtable else-symtable pos)

  (hash-union if-symtable else-symtable
              #:combine/key (lambda (id if-type else-type)
                              (if (equal? if-type else-type)
                                  if-type
                                  (raise-type-consistency-error pos id if-type else-type)))))

;; While
;; <returns> statement, symtables
(define (typecheck-while test body pos symtables expected-return-type)
  ; typecheck test expression
  (let-values ([(test test-type) (typecheck-expr test symtables)])
    ; convert test to bool
    (let ([test
           (match test-type
             [(== std-int)   test]
             [(== std-bool)  test]
             [(== std-str)   (ast-call "str_to_bool" (list test))]
             [(== std-none)  (ast-call "none_to_bool" (list test))]
             [(std-func _ _) (ast-call "func_to_bool" (list test))])])
      ; typecheck body statements
      (let-values ([(body symtables) (typecheck-stmts body symtables expected-return-type #f)])
        (values (ast-while test body)
                symtables)))))

;; Function definition
;; <returns> statement, symtables
(define (typecheck-funcdef id return-type params body pos symtables)
  (define local-symtable (first symtables))
  ; check for existing symbol with same id
  (when (hash-has-key? local-symtable id)
    (raise-name-already-declared-error pos id))

  ; update local symtable (before body typecheck, to allow recursivity)
  (let* ([params-types (map (lambda (param) (match param [(ast-pos-param _ type _) type]))
                            params)]
         [type (std-func return-type params-types)])
    (let* ([local-symtable (hash-set local-symtable id type)]
           [symtables (cons local-symtable (rest symtables))])
      ; new symtable for function body with functions params
      (define inner-symtable (hash))
      (define inner-symtables (cons inner-symtable symtables))
      ; typecheck parameters with inner symbol tables
      (let-values ([(params inner-symtables) (typecheck-params params pos inner-symtables)])
        ; return-type defaults to none
        (let ([return-type (or return-type std-none)])
          ; typecheck body with inner symbol tables and expected return type
          (let-values ([(body _) (typecheck-stmts body inner-symtables return-type)])
            (values (ast-funcdef id return-type params body)
                    symtables)))))))

;; Function params
;; <returns> statements, symtables
(define (typecheck-params params pos symtables)
  (define local-symtable (first symtables))
  (let-values
      ([(params local-symtable)
        (for/fold ([params (list)]
                   [local-symtable local-symtable])
                  ([param params])
          (match param
            [(ast-pos-param id type pos)
             ; check for existing param with same id
             (when (hash-has-key? local-symtable id)
               (raise-duplicate-param-error pos id))
             (let ([param (ast-param id type)])
               (values (append params (list param))
                       (hash-set local-symtable id type)))]))])
    (values params
            (cons local-symtable (rest symtables)))))

;; Expression
;; <returns> statement, type
(define (typecheck-expr expr symtables)
  (match expr
    [(ast-pos-num val pos)
     (typecheck-num val pos)]
    [(ast-pos-const val pos)
     (typecheck-const val pos)]
    [(ast-pos-str val pos)
     (typecheck-str val pos)]
    [(ast-pos-name id pos)
     (typecheck-name id pos symtables)]
    [(ast-pos-binoper op lhs rhs pos)
     (typecheck-binoper op lhs rhs pos symtables)]
    [(ast-pos-unoper op operand pos)
     (typecheck-unoper op operand pos symtables)]
    [(ast-pos-subscript value index pos)
     (typecheck-subscript value index pos symtables)]
    [(ast-pos-call func args pos)
     (typecheck-call func args pos symtables)]))

;; Num
;; <returns> expression, type
(define (typecheck-num val pos)
  ; only integers are supported
  (values (ast-num val)
          std-int))

;; Const
;; <returns> statement, type
(define (typecheck-const val pos)
  (match val
    [(or 'true 'false) (values (ast-const val)
                               std-bool)]
    ['none             (values (ast-const std-none)
                               std-none)]))

;; String
;; <returns> statement, type
(define (typecheck-str val pos)
  (values (ast-str val)
          std-str))

;; Name
;; <returns> statement, type
(define (typecheck-name id pos symtables)
  (define type (resolve-id id pos symtables))
  (values (ast-name id)
          type))

;; Binary operation
;; all operations are replaced by calls
;; <returns> statement, type
(define (typecheck-binoper op lhs rhs pos symtables)
  ; typecheck operands
  (let-values ([(lhs lhs-type) (typecheck-expr lhs symtables)]
               [(rhs rhs-type) (typecheck-expr rhs symtables)])
    ; identify operation using operator and operand types
    (define op-key (list op lhs-type rhs-type))
    (when (not (hash-has-key? std-ops op-key))
      (raise-binop-type-error pos op lhs-type rhs-type))
    ; replace operation by call to internal function
    (let ([func-desc (hash-ref std-ops op-key)])
      (define func-name (car func-desc))
      (define return-type (cdr func-desc))
      (values (ast-call func-name (list lhs rhs))
              return-type))))

;; Unary operation
;; all operations are replaced by calls
;; <returns> statement, type
(define (typecheck-unoper op operand pos symtables)
  ; typecheck operand
  (let-values ([(operand operand-type) (typecheck-expr operand symtables)])
    ; identify operation using operator and operand types
    (define op-key (list op operand-type))
    (when (not (hash-has-key? std-ops op-key))
      (raise-unop-type-error pos op operand-type))
    ; replace operation by call to internal function
    (let ([func-desc (hash-ref std-ops op-key)])
      (define func-name (car func-desc))
      (define return-type (cdr func-desc))
      (values (ast-call func-name (list operand))
              return-type))))

;; Subscript
;; all subscripts accesses are replaced by calls
;; <returns> statement, type
(define (typecheck-subscript value index pos symtables)
  ; check value is a string (TODO or a list)
  (let-values ([(value value-type) (typecheck-expr value symtables)])
    (match value-type
      ; string: get char index
      [(== std-str)
       ; typecheck index expression
       (let-values ([(index index-type) (typecheck-expr index symtables)])
         ; check index type is int or bool
         (let ([index
                (match index-type
                  [(== std-int)  index]
                  [(== std-bool) index];(ast-call "bool_to_int" (list index))]
                  [_ (raise-invalid-index-type-error pos value-type)])])
           (values (ast-call "char_at_index" (list value index))
                   std-str)))] ; returns a string
      ; TODO list
      ; not subscriptable
      [_ (raise-not-subscriptable-error pos value-type)])))

;; Call
;; <returns> statement, type
(define (typecheck-call callee args pos symtables)
  ; check callee is a function
  (define callee-type (resolve-id callee pos symtables))
  ;(let-values ([(callee callee-type) (typecheck-expr callee symtables)])
  (match callee-type
    ; function
    [(std-func return-type param-types)
     ; typecheck args
     (let-values ([(args _) (typecheck-args param-types args pos symtables)])
       (values (ast-call callee args)
               return-type))]
    ; not callable
    [_ (raise-not-callable-error pos callee-type)]))

;; Call arguments
;; <params-types> types of formal parameters
;; <args> actual arguments
;; <returns> statements, types
(define (typecheck-args params-types args pos symtables)
  ; check arity
  (define params-count (length params-types))
  (define args-count (length args))
  (when (not (equal? params-count args-count))
    (raise-arity-error pos params-count args-count))
  ; check arguments
  (for/lists (args types) ([param-type params-types]
                           [arg args])
    ; typecheck value expression
    (define-values (expr expr-type) (typecheck-expr arg symtables))
    ; check types matches parameter
    (unless (equal? param-type expr-type)
      (raise-arg-type-error pos param-type expr-type))
    (values expr
            expr-type)))
