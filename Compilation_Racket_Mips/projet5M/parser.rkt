#lang racket/base

(require parser-tools/yacc
         racket/port
         "lexer.rkt"
         "ast.rkt")

(provide gawi-parser)

(define parse
  (parser
   (src-pos)
   (tokens keywords-and-operators values-and-names)
   (grammar
    (prog
     ((block)      (list $1))
     ((block prog) (cons $1 $2)))
    (block
    ((Ldef Lident Lopar names Lcpar Loacc body Lreturn names Lsc Lcacc) 
        (Pblock $2 $4 $9 $7 $11-end-pos))
      )
    (names
     ((Lident)       (list $1))
     ((Lident Lco names) (cons $1 $3)))
    (body
     ((instr)          (list $1))
     ((instr body) (cons $1 $2)))
    (instr
     ((names Lassign expr Lsc) (Passign $1 $3 $2-start-pos)))
    (expr
     ((arg)            $1)
     ((Lident Lopar args Lcpar)    (Pcall $1 $3 $1-start-pos))
     ((expr Ladd expr) (Pcall '%add (list $1 $3) $2-start-pos))
     ((expr Lsub expr) (Pcall '%sub (list $1 $3) $2-start-pos))
     ((expr Lmul expr) (Pcall '%mul (list $1 $3) $2-start-pos))
     ((expr Ldiv expr) (Pcall '%div (list $1 $3) $2-start-pos))
     ((expr Land expr) (Pcall '%and (list $1 $3) $2-start-pos))
     ((expr Lor expr)  (Pcall '%or  (list $1 $3) $2-start-pos))
     ((expr Lxor expr) (Pcall '%xor (list $1 $3) $2-start-pos))
     ((Lnot expr)      (Pcall '%not (list $2) $1-start-pos))
     )
    (args
     ((arg)      (list $1))
     ((arg Lco args) (cons $1 $3)))
    (arg
     ((Lident) (Pident $1 $1-start-pos))
     ((Lbool)  (Pbit $1 $1-start-pos))
     ((Lopar expr Lcpar) $2)))
   (start prog)
   (end Lend)
   (precs (left Lor) (left Lxor) (left Land) (right Lnot))
   (debug "yacc.dbg")
   (error (lambda (ok? name value s-pos e-pos)
            (eprintf "Parser: syntax error near ~a~a on line ~a col ~a.\n"
                     name (if value (format " (~a)" value) "")
                     (position-line s-pos) (position-col s-pos))
            (exit 1)))))

(define (gawi-parser in)
  (parse (lambda () (gawi-lexer in))))

