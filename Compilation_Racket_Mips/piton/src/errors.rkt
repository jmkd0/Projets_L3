#lang racket/base

(require (prefix-in std- "types.rkt")
         parser-tools/lex
         racket/match
         racket/list)
(provide (all-defined-out))

(define (raise-error type . message-with-params)
  (eprintf (string-append (symbol->string type) ": "))
  (apply eprintf message-with-params)
  (eprintf "\n")
  (exit 1))

(define (raise-error-with-pos type pos . message-with-params)
  (eprintf (string-append (symbol->string type) ": "))
  (apply eprintf message-with-params)
  (eprintf "\nAt line ~a col ~a\n" (position-line pos) (position-col pos))
  (exit 1))

(define (raise-lexer-error pos lexeme)
  (raise-error-with-pos 'LexerError pos "unrecognized character '~a'"
                        lexeme))

(define (raise-unterminated-str-error pos)
  (raise-error-with-pos 'LexerError pos "unterminated string literal"))

(define (raise-tab-error)
  (raise-error 'TabError "inconsistent use of tabs and spaces in indentation"))

(define (raise-unindent-error)
  (raise-error 'IndentationError "unindent does not match any outer indentation level"))

(define (raise-syntax-error pos token)
  (raise-error-with-pos 'SyntaxError pos "invalid syntax near '~a'"
                        (token->string token)))

(define (raise-undeclared-name-error pos name)
  (raise-error-with-pos 'NameError pos "name '~a' is not defined"
                        name))

(define (raise-name-already-declared-error pos name)
  (raise-error-with-pos 'DeclarationError pos "name '~a' already declared"
                        name))

(define (raise-duplicate-param-error pos name)
  (raise-error-with-pos 'DeclarationError pos "duplicate parameter '~a' in function definition"
                        name))

(define (raise-funcdef-not-allowed-error pos)
  (raise-error-with-pos 'DeclarationError pos "function declaration not allowed inside if, else or while body"))

;; Unbound local
;(define (raise-unbound-local-error pos name)
;  (raise-user-error 'UnboundLocalError "local variable '~a' referenced before assignment" name))

(define (raise-type-consistency-error pos name first-type sec-type)
  (raise-error-with-pos 'TypeError pos "conflicting types declarations for variable '~a' in if and else branches"
                        name))

(define (raise-assign-type-error pos var-name var-type val-type)
  (raise-error-with-pos 'TypeError pos "cannot assign ~a value to name '~a' of type ~a"
                        (type->string val-type) var-name (type->string var-type)))

(define (raise-assign-func-error pos)
  (raise-error-with-pos 'AssignError pos "reassigning a function is not allowed"))


(define (raise-not-callable-error pos type)
  (raise-error-with-pos 'TypeError pos "~a value is not callable"
                        (type->string type)))

(define (raise-not-subscriptable-error pos type)
  (raise-error-with-pos 'TypeError pos "~a value is not subscriptable"
                        (type->string type)))

(define (raise-invalid-index-type-error pos type)
  (raise-error-with-pos 'TypeError pos "invalid index type ~a"
                        (type->string type)))

; params: formal parameters, args: actual arguments
(define (raise-arity-error pos params-count args-count)
  (if (> params-count args-count)
      ; not enough
      (let* ([missing-count (- params-count args-count)]
             [missing-string (if (equal? 1 missing-count) "parameter" "parameters")])
        (raise-error-with-pos 'TypeError pos "function missing ~a ~a"
                              missing-count missing-string))
      ; too much
      (let ([params-string (if (equal? 1 params-count) "parameter" "parameters")])
        (raise-error-with-pos 'TypeError pos "function takes ~a ~a but ~a were given"
                              params-count params-string args-count))))

(define (raise-binop-type-error pos op lhs-type rhs-type)
  (raise-error-with-pos 'TypeError pos "operand types ~a and ~a are unsupported for ~a"
                        (type->string lhs-type) (type->string rhs-type) op))

(define (raise-unop-type-error pos op operand-type)
  (raise-error-with-pos 'TypeError pos "operand type ~a is unsupported for ~a"
                        (type->string operand-type) op))

(define (raise-arg-type-error pos param-type arg-type)
  (raise-error-with-pos 'TypeError pos "cannot pass ~a value to parameter of type ~a"
                        (type->string arg-type) (type->string param-type)))

(define (raise-return-type-error pos return-type func-return-type)
  (raise-error-with-pos 'TypeError pos "cannot return ~a value from function with return type ~a"
                        (type->string return-type) (type->string func-return-type)))


(define (type->string type)
  (match type
    [(? std-func?)     "function"]
    [(== std-none)     "NoneType"]
    [_ (symbol->string type)]))

(define (token->string token)
  (match token
    [(? string?) token]
    [(? symbol?) (symbol->string token)]
    [(? list?)   (token->string (first token))]
    [_           token]))
