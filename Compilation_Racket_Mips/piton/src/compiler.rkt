#lang racket/base

(require racket/list
         racket/match
         (prefix-in ast- "ast.rkt")
         (prefix-in std- "compiled-builtin.rkt")
         "mips.rkt"
         "call-simplifier.rkt"
         "mips-helper.rkt")
(provide compile)
(require racket/pretty)

;; <return> mips instructions
;; arguments are passed on stack rather than through $a0-$a3
;; $v0 is used for return values
;; $t9 registrer is reserved for tests and quick one-shot operations (mem-to-mem moves, etc)
;; $t8 registrer is reserved for outer scope variable fetching
;; $s registers are never used
(define (compile ast)
  ; prepare built-in funcs
  (define-values (builtin-funcs-instrs builtin-symtable) (assemble-builtin-funcs))
  ; prepare main function
  (define main-symtable (build-symtable ast 1))
  (let ([main-symtable (hash-set main-symtable "main" (cons 1 "main"))])
    ; local and built-in scopes (no global, but main is sort of global)
    (define symtables (list main-symtable builtin-symtable))
    ; compile function definitions in main
    (define func-instrs (compile-funcdefs ast symtables))
    (define frame-size (symtable-frame-size main-symtable))
    (define instrs
      (append builtin-funcs-instrs
              func-instrs
              (list (label "main"))
              (compile-stmts ast symtables frame-size)
              (list (jr $ra))))

    ; separe data and text instructions
    (define-values (data-instrs text-instrs) (partition data-instr? instrs))
    (append (list (data-section))
            data-instrs
            (list (text-section)
                  (globl "main"))
            text-instrs)))

;; <return> instructions, symbols table
(define (assemble-builtin-funcs)
  (for/fold ([instrs (list)]
             [symtable (hash)])
            ([name (hash-keys std-lib)]
             [func (hash-values std-lib)])
    ; generate random id to avoid name clashes
    (define mips-id (string-append "func_" (symbol->string (gensym))))
    (values (append instrs
                    (list (comment (string-append "func " name))
                          (label mips-id))
                    (func))
            ; level 0, outmost level (built-in scope)
            (hash-set symtable name (cons 0 mips-id)))))

;; <return> size of frame occupied by symbols of symtable (number of local vars)
(define (symtable-frame-size symtable)
  (+ 1 (count (lambda (sym) (number? (cdr sym))) (hash-values symtable))))

;; <return> instructions, location (label or mem address)
(define (resolve-id id symtables [level-offset 0])
  (when (empty? symtables) ; for debug
    (raise-user-error (format "Symbol not found '~a'" id)))
  (let ([symtable (first symtables)])
    (if (hash-has-key? symtable id)
        (match (cdr (hash-ref symtable id))
          ; label: always accessible
          [mips-id
           #:when (string? mips-id)
           (label mips-id)]
          ; mem address relative to sp: use access link
          [stack-offset
           #:when (number? stack-offset)
           (if (equal? 0 level-offset)
               (mem stack-offset $sp)
               (outer-mem level-offset stack-offset))])
        (resolve-id id (rest symtables) (+ 1 level-offset)))))

;; <return> symbol level (outmost = 0)
;; based on scope in which it was declared/defined
(define (level-for-symbol symtables id)
  (when (empty? symtables) ; for debug
    (raise-user-error (format "Symbol not found '~a'" id)))
  (let ([symtable (first symtables)])
    (if (hash-has-key? symtable id)
        (car (hash-ref symtable id))
        (level-for-symbol (rest symtables) id))))

;; Add ids of local variable declarations and function definitions to <symtable>
;; <return> symbol table
;; a symbol table hash table with ids as key and (level . mips-id-or-offset) as values
;; <level>: depth of scope in which symbol is declared/defined
;; mips-id-or-offset: auto generated label for functions and offset to $sp for variables
(define (build-symtable stmts level [symtable (hash)])
  (for/fold ([symtable symtable])
            ([stmt stmts])
    (match stmt
      ; variable declaration or function parameter
      [(or (ast-decl id _ _) (ast-param id _))
       ; multiple declarations may occur (if/else), first one prevails
       ; (important for stack order)
       (if (hash-has-key? symtable id)
           symtable
           (let ([stack-offset (* -4 (symtable-frame-size symtable))])
             ; location is mem relative to stack
             (hash-set symtable id (cons level stack-offset))))]
      ; function definition
      [(ast-funcdef id return-type params body)
       ; multiple declarations may occur (if/else), first one prevails
       (if (hash-has-key? symtable id)
           symtable
           ; generate random id to avoid name clashes
           (let ([mips-id (string-append "func_" (symbol->string (gensym)))])
             (hash-set symtable id (cons level mips-id))))]
      ; declarations in test if block and in if/else bodies
      [(ast-if test body else-body)
       (let ([symtable (match test
                         [(ast-block body) (build-symtable body level symtable)]
                         [_ symtable])])
         (if else-body
             (let ([symtable (build-symtable body level symtable)])
               (build-symtable else-body level symtable))
             (build-symtable body level symtable)))]
      ; declarations in while test if block and in and body
      [(ast-while test body)
       (let ([symtable (match test
                         [(ast-block body) (build-symtable body level symtable)]
                         [_ symtable])])
         (build-symtable body level symtable))]
      ; declarations in block body
      [(ast-block body)
       (build-symtable body level symtable)]
      ; anything else: nothing to do
      [_ symtable])))

;; Compile local function definitions in <stmts>
;; <return> instructions
(define (compile-funcdefs stmts symtables)
  (for/fold ([instrs (list)])
            ([stmt stmts])
    (match stmt
      ; function definition
      [(ast-funcdef id return-type params body)
       (define func-instrs (compile-funcdef id return-type params body symtables))
       (append instrs func-instrs)]
      ; anything else: nothing to do
      [_ instrs])))

;; Function definition
;; <return> instructions
(define (compile-funcdef id return-type params body symtables)
  ; construct inner scope symtable
  (define level (length symtables))
  (define inner-symtable (build-symtable params level))
  (let ([inner-symtable (build-symtable body level inner-symtable)])
    (define body-symtables (cons inner-symtable symtables))
    ; compile nested function declarations first
    (define body-funcs-instrs (compile-funcdefs body body-symtables))
    ; retrieve from symbol table the auto generated label
    (define mips-id (cdr (hash-ref (first symtables) id)))
    ; 1 because activation link is already on stack
    (define frame-size (+ 1 (symtable-frame-size inner-symtable)))
    (append body-funcs-instrs
            (list (comment (string-append "func " id))
                  (label mips-id))
            (compile-stmts body body-symtables frame-size)
            (list (jr $ra)))))

;; Group of statements
;; <return> instructions
(define (compile-stmts stmts symtables frame-size [in-block? #f])
  (for/fold ([instrs (list)])
            ([stmt stmts])
    (append instrs
            (compile-stmt stmt symtables frame-size in-block?))))

;; Statement
;; <return> instructions
(define (compile-stmt stmt symtables frame-size [in-block? #f])
  (match stmt
    ; variable declaration
    [(ast-decl id type value)
     ; declaration part already handled by <build-symtables>
     ; assignation part identical to ast-assign
     (compile-assign id value symtables frame-size)]
    ; assignation
    [(ast-assign target value)
     (compile-assign target value symtables frame-size)]
    ; return
    [(ast-return value)
     (compile-return value symtables frame-size in-block?)]
    ; if
    [(ast-if test body else-body)
     (compile-if test body else-body symtables frame-size)]
    ; while
    [(ast-while test body)
     (compile-while test body symtables frame-size)]
    ; function definition: already compiled by <compile-funcdefs>
    [(ast-funcdef name return-type params body) empty]
    ; anything else is an expression, result is ignored
    [_ (compile-expr stmt #f symtables frame-size)]))

;; Assignation
;; <return> instructions
(define (compile-assign target value symtables frame-size)
  (define target-loc (resolve-id target symtables))
  (compile-expr value target-loc symtables frame-size))

;; Return
;; <return> instructions
(define (compile-return value symtables frame-size in-block?)
  ; test block: put result in $t9 and no call to jr
  (if in-block?
      (compile-expr value $t9 symtables frame-size)
      (append (compile-expr value $v0 symtables frame-size)
              (list (jr $ra)))))

;; If
;; <return> instructions
(define (compile-if test body else-body symtables frame-size)
  ; prepare labels
  (define if-id (symbol->string (gensym)))
  (define if-label (label (string-append "if_" if-id)))
  (define else-label (label (string-append "else_" if-id)))
  (define endif-label (label (string-append "endif_" if-id)))

  ; compile test first
  (define test-instrs
    ; $t9 register used for tests
    (match test
        [(ast-block body) (compile-block body $t9 symtables frame-size)]
        [_ (compile-expr test $t9 symtables frame-size)]))

  (append (list if-label) ; here for clarity only
          test-instrs
          (list (beqz $t9 else-label))
          (compile-stmts body symtables frame-size)
          (list (b endif-label)
                else-label)
          (if else-body
              (compile-stmts else-body symtables frame-size)
              (list (nop)))
          (list endif-label)))

;; While
;; <return> instructions
(define (compile-while test body symtables frame-size)
  ; prepare labels
  (define while-id (symbol->string (gensym)))
  (define while-label (label (string-append "while_" while-id)))
  (define endwhile-label (label (string-append "endwhile_" while-id)))

  ; compile test first
  (define test-instrs
    ; $t9 register used for tests
    (match test
        [(ast-block body) (compile-block body $t9 symtables frame-size)]
        [_ (compile-expr test $t9 symtables frame-size)]))

  (append (list while-label)
          test-instrs
          (list (beqz $t9 endwhile-label))
          (compile-stmts body symtables frame-size)
          (list (b while-label)
                endwhile-label)))

;; Expression
;; <return> instructions
(define (compile-expr expr dest-loc symtables frame-size)
  (match expr
    [(ast-num value)        (compile-num value dest-loc)]
    [(ast-const value)      (compile-const value dest-loc)]
    [(ast-str value)        (compile-str value dest-loc)]
    [(ast-name id)          (compile-name id dest-loc symtables frame-size)]
    [(ast-call callee args) (compile-call callee args dest-loc symtables frame-size)]))

;; Num
;; <return> instructions
(define (compile-num value dest-loc)
  (move-val dest-loc value))

;; Const
;; <return> instructions
(define (compile-const value dest-loc)
  (match value
    ['true  (move-val dest-loc 1)]
    ['false (move-val dest-loc 0)]
    ['none  (move-val dest-loc 0)]))

;; String
; <return> instructions
(define (compile-str value dest-loc)
  (define str-id (symbol->string (gensym)))
  (define str-label (label (string-append "str_" str-id)))
  (append (list (asciiz str-label value))
          (move-val dest-loc str-label)))

;; Name
;; <return> instructions
(define (compile-name id dest-loc symtables frame-size)
  (move-val dest-loc (resolve-id id symtables)))

;; Block (used only in test conditions)
;; <return> instructions
(define (compile-block body dest-loc symtables frame-size)
  (compile-stmts body symtables frame-size #t))

;; Call
;; <return> instructions
(define (compile-call callee args dest-loc symtables frame-size)
  (if (hash-has-key? std-lib-inlined callee)
      (compile-inlined-call callee args dest-loc symtables frame-size)
      (compile-real-call callee args dest-loc symtables frame-size)))

;; Inlined call
;; copy instructions from builtin function instead of jumping
;; <return> instructions
(define (compile-inlined-call callee args dest-loc symtables frame-size)
  ;; ok to put arguments in $a registers because we know there are no nested
  ;; calls so they will not be overwritten
  ;; TODO unnecessary ? directly pass arg locs?
  (define a-regs (list $a0 $a1 $a2 $a3))
  (define args-instrs
    (for/fold ([args-instrs (list)])
              ([arg args]
               [i (length args)])
      (define dest-loc (list-ref a-regs i))
      (define expr-instrs (compile-expr arg dest-loc symtables frame-size))
      (append args-instrs expr-instrs)))

  ; insert mips code
  (define func (hash-ref std-lib-inlined callee))
  (define func-instrs (func dest-loc a-regs))
  (append args-instrs
          func-instrs))

;; Real call
;; <return> instructions, value ($v0)
(define (compile-real-call callee args dest-loc symtables frame-size)
  (define caller-level (- (length symtables) 1))
  (define callee-level (level-for-symbol symtables callee))
  (define callee-loc (resolve-id callee symtables))
  ; jump to label or address in register
  (define jump-instrs
    (match callee-loc
      [(? label?)     (list (jal callee-loc))]
      [(? reg?)       (list (jalr callee-loc))]
      [(? outer-mem?) (append (move-val $t9 callee-loc)
                              (list (jalr $t9)))]))
  ;(pretty-print (compile-args args symtables frame-size))
  ; push $ra on stack before activation link and arguments
  ; thanks to call-simplifier, arguments cannot trigger calls
  ; so it is safe to push $ra before arguments instructions are exectued
  (append (compile-args args symtables frame-size) ; + 2 because of $ra and activlnk
          (list (sw $ra (mem (* frame-size -4) $sp)))
          ; push activation link on stack after $ra, before arguments
          (push-next-activlnk caller-level callee-level
                              (mem (* (+ frame-size 1) -4) $sp))
          ; execute argument expressions and push them on stack
          (list (addi $sp $sp (* (+ frame-size 1) -4)))
          jump-instrs
          (list (addi $sp $sp (* (+ frame-size 1) 4))
                (lw $ra (mem (* frame-size -4) $sp)))
          (move-val dest-loc $v0)))

;; Call arguments
;; <return> instructions, number of args
;; arguments are pushed to stack
(define (compile-args args symtables frame-size)
  (for/fold ([instrs (list)])
            ([arg args]
             [i (length args)])
    ; + 2 because arguments are added after $ra and activation link
    (define stack-offset (* (+ frame-size i 2) -4))
    (define dest-loc (mem stack-offset $sp))
    (define expr-instrs (compile-expr arg dest-loc symtables (+ frame-size i)))
    (append instrs expr-instrs)))
