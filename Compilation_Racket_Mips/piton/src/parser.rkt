#lang racket/base

(require (prefix-in yacc- parser-tools/yacc)
         parser-tools/lex
         racket/list
         racket/function
         data/queue
         (prefix-in lex- "lexer.rkt")
         (prefix-in ast- "ast.rkt")
         "errors.rkt")
(provide parse)

;; Lexer wrapper
;; detects multiple tokens and queue them
(define (enqueue-next-tokens token-queue in)
  ; get next pos-token from lexer
  (define pos-token (lex-main-lexer in))
  ; unwrap actual token or tokens
  (define token-or-tokens (position-token-token pos-token))
  (if (not (list? token-or-tokens))
      ; single token: enqueue directly pos-token
      (enqueue! token-queue pos-token)
      ; multiple tokens: rewrap each one in a new pos-token
      ; before enqueuing them
      (let ([start-pos (position-token-start-pos pos-token)]
            [end-pos (position-token-end-pos pos-token)])
        (for ([token token-or-tokens])
          (define pos-token (make-position-token token start-pos end-pos))
          (enqueue! token-queue pos-token)))))

(define (parse in)
  (define token-queue (make-queue))
  (parser (thunk
           ; enqueue new tokens from lexer if queue is empty
           (when (queue-empty? token-queue)
             (enqueue-next-tokens token-queue in))
           (let ([token (dequeue! token-queue)])
             ;(println (position-token-token token))
             token))))

(define parser
  (yacc-parser
   (src-pos)
   (tokens lex-keywords lex-delimiters lex-operators lex-atoms)
   (start prog)
   (end eof)

   (grammar
    ;; Program
    (prog
     ((stmt prog)    (cons $1 $2))
     ((stmt)         (list $1))
     ; allow empty lines
     ((eol prog)     $2)
     ((eol)          (list)))
    ;; Statement
    (stmt
     ((simple-stmt eol) $1)
     ((compound-stmt)   $1))
    ;; Simple statement
    (simple-stmt
     ((expr)   $1)
     ((name col type assign-op expr) (ast-pos-decl $1 $3 $5 $1-start-pos))
     ;((atom assign-op expr)         (ast-pos-assign $1 $3 $1-start-pos)))
     ((name assign-op expr)          (ast-pos-assign $1 $3 $1-start-pos))
     ((return-stmt)                  $1))
    (return-stmt
     ((return expr) (ast-pos-return $2 $1-start-pos))
     ((return)      (ast-pos-return #f $1-start-pos)))

    ;; Compound statement
    (compound-stmt
     ((if-stmt) $1)
     ((while-stmt) $1)
     ((funcdef) $1))

    ;; Expression
    (expr
     ((atom)                $1)
     ((call)                $1)
     ((binoper)                $1)
     ((unoper)                $1))

    ;; Atom
    (atom
     ((num)            (ast-pos-num $1 $1-start-pos))
     ((str)            (ast-pos-str $1 $1-start-pos))
     ((const)          (ast-pos-const $1 $1-start-pos))
     ((name)           (ast-pos-name $1 $1-start-pos))
     ((subscript)      $1)
     ((opar expr cpar) $2))

    ;; Call
    (call
     ;((atom args-with-pars) (ast-pos-call $1 $3 $1-start-pos))
     ((name args-with-pars) (ast-pos-call $1 $2 $1-start-pos)))
    ;; Call arguments
    (args-with-pars
     ((opar args cpar) $2)
     ((opar cpar)      empty))
    (args
     ((expr comma args) (cons $1 $3))
     ((expr)            (list $1)))

    ;; Subscript
    (subscript
     ((atom obra expr cbra) (ast-pos-subscript $1 $3 $1-start-pos)))

   ;; Operation
    (binoper
     ((expr add expr)  (ast-pos-binoper '+ $1 $3 $1-start-pos))
     ((expr sub expr)  (ast-pos-binoper '- $1 $3 $1-start-pos))
     ((expr mul expr)  (ast-pos-binoper '* $1 $3 $1-start-pos))
     ((expr div expr)  (ast-pos-binoper '/ $1 $3 $1-start-pos))
     ((expr land expr) (ast-pos-binoper 'land $1 $3 $1-start-pos))
     ((expr lor expr)  (ast-pos-binoper 'lor $1 $3 $1-start-pos))
     ((expr eq expr)   (ast-pos-binoper '== $1 $3 $1-start-pos))
     ((expr neq expr)  (ast-pos-binoper '!= $1 $3 $1-start-pos))
     ((expr gt expr)   (ast-pos-binoper '> $1 $3 $1-start-pos))
     ((expr lt expr)   (ast-pos-binoper '< $1 $3 $1-start-pos))
     ((expr gte expr)  (ast-pos-binoper '>= $1 $3 $1-start-pos))
     ((expr lte expr)  (ast-pos-binoper '<= $1 $3 $1-start-pos)))

    (unoper
     ((lnot expr) (ast-pos-unoper 'lnot $2 $1-start-pos)))

    ;; If
    (if-stmt
     ((if expr col suite else col suite) (ast-pos-if $2 $4 $7 $1-start-pos))
     ((if expr col suite)                (ast-pos-if $2 $4 #f $1-start-pos)))
    ;; While
    (while-stmt
     ((while expr col suite) (ast-pos-while $2 $4 $1-start-pos)))

    ;; Function definition
    (funcdef
     ((def name params-with-pars arrow type col suite) (ast-pos-funcdef $2 $5 $3 $7 $1-start-pos))
     ((def name params-with-pars col suite)            (ast-pos-funcdef $2 #f $3 $5 $1-start-pos)))
    ;; Function parameters
    (params-with-pars
     ((opar params cpar) $2)
     ((opar cpar)        empty))
    (params
     ((param comma params) (cons $1 $3))
     ((param)              (list $1)))
    (param
     ((name col type) (ast-pos-param $1 $3 $1-start-pos)))

    ;; Suite
    (suite
     ((simple-stmt eol)        (list $1))
     ((eol indent suite-stmts) $3))
    (suite-stmts
     ((stmt suite-stmts) (cons $1 $2))
     ((stmt dedent)      (list $1))
     ; allow empty lines
     ((eol suite-stmts)  $2)
     ((eol dedent)       (list))))

   ;; Operator precedence
   (precs
    (left lor)
    (left land)
    (right lnot)
    (left eq)
    (left neq)
    (left lt)
    (left gt)
    (left lte)
    (left gte)
    (left add)
    (left sub)
    (left mul)
    (left div))

   (error (lambda (tok-ok? tok-name tok-value start-pos end-pos)
            (raise-syntax-error start-pos (if tok-value tok-value tok-name))))))
   ;(debug "yacc.dbg")))
