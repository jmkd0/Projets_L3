#lang racket/base

(require (only-in parser-tools/lex position-line position-col)
         racket/match
         racket/string
         "ast.rkt"
         "stdlib.rkt")

(provide analyze)

;; fonctions d'aide à la gestion des erreurs

(define (fail! msg)
  (eprintf "Fatal error: ~a.\n" msg)
  (exit 1))

(define (err msg pos)
  (eprintf "Error on line ~a col ~a: ~a.\n"
           (position-line pos)
           (position-col pos)
           msg)
  (exit 1))

(define (type->string t)
  (match t
    ['bool "boolean"]
    ['num  "number"]
    [(Fun r a)
     (string-append (if (> (length a) 1) "(" "")
                    (string-join (map type->string a) ", ")
                    (if (> (length a) 1) ")" "")
                    " -> " (type->string r))]))

(define (expr-pos expr)
  (match expr
    [(Pbool _ pos)     pos]
    [(Pnum _ pos)      pos]
    [(Pvar _ pos)      pos]
    [(Pcall _ _ pos)   pos]
    [(Pcond _ _ _ pos) pos]
    [else (fail! "not an expression")]))

(define (errt expected given pos)
  (err (format "expected ~a but given ~a"
               (type->string expected)
               (type->string given))
       pos))

;; analyse sémantique

(define (analyze parsed)
  (analyze-prog parsed))

(define (analyze-prog prog)
  (match prog
    [(list)
     null]
    [(cons i p)
     (let ([ai (analyze-instr i)])
       (cons ai (analyze-prog p)))]))

(define (analyze-instr instr)
  (match instr
    [(Passign v e pos)
     (let ([ae (analyze-expr e)])
       (Assign v ae))]
    [else (fail! "not an instruction")]))

(define (analyze-expr expr)
  (match expr
    [(Pbool b pos)
     (Bool b)]
    [(Pnum n pos)
     (Num n)]
    [(Pvar v pos)
     (Var v)]
    [(Pcall f as pos)
     (let ([aas (map analyze-expr as)])
       (Call f aas))]
    [(Pcond t y n pos)
     (let ([at (analyze-expr t)]
           [ay (analyze-expr y)]
           [an (analyze-expr n)])
       (Cond at ay an))]
    [else (fail! "not an expression")]))
