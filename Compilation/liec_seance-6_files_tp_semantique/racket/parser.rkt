#lang racket/base

(require parser-tools/lex
         parser-tools/yacc
         "lexer.rkt"
         "ast.rkt")

(provide parse)

(define parse
  (parser
   (src-pos)
   (tokens keywords-and-operators names-and-values)
   (start prog)
   (end Lend)
   (grammar
    (prog
     ((instr) (list $1))
     ((instr prog) (cons $1 $2)))
    (instr
     ((Lvar Lassign expr Lsc) (Passign $1 $3 $1-start-pos)))
    (expr
     ((Lbool)     (Pbool $1 $1-start-pos))
     ((Lsub Lnum) (Pnum (- $2) $1-start-pos))
     ((Lnum)      (Pnum $1 $1-start-pos))
     ((Lvar)      (Pvar $1 $1-start-pos))
     ((expr Ladd expr) (Pcall '%add (list $1 $3) $2-start-pos))
     ((expr Lsub expr) (Pcall '%sub (list $1 $3) $2-start-pos))
     ((expr Lmul expr) (Pcall '%mul (list $1 $3) $2-start-pos))
     ((expr Ldiv expr) (Pcall '%div (list $1 $3) $2-start-pos))
     ((Lif expr Lthen expr Lelse expr) (Pcond $2 $4 $6 $1-start-pos))
     ((expr Leq expr)  (Pcall '%eq  (list $1 $3) $2-start-pos))
     ((expr Lneq expr) (Pcall '%neq (list $1 $3) $2-start-pos))
     ((expr Llt expr)  (Pcall '%lt  (list $1 $3) $2-start-pos))
     ((expr Lgt expr)  (Pcall '%gt  (list $1 $3) $2-start-pos))
     ((expr Llte expr) (Pcall '%lte (list $1 $3) $2-start-pos))
     ((expr Lgte expr) (Pcall '%gte (list $1 $3) $2-start-pos))
     ((Lopar expr Lcpar) $2)))
   (precs (right Lelse)
          (left Leq Lneq Llt Lgt Llte Lgte)
          (left Ladd Lsub)
          (left Lmul Ldiv))
   (error
    (lambda (ok? name value s-pos e-pos)
      (eprintf "Parser: syntax error near ~a~a on line ~a col ~a.\n"
               name
               (if value (format " (~a)" value) "")
               (position-line s-pos)
               (position-col s-pos))
      (exit 1)))))
