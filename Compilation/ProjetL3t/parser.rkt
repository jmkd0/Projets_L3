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
    ((Ldef Lvar Lopar names Lcpar Lopar names Lcpar Loacc body Lcacc) 
        (Pblock $2 $4 $7 $10 $11-end-pos)))
    (names
     ((Lvar)       (list $1))
     ((Lvar Lco names ) (list $1 $3)))
    (body 
    ((instr)        (list $1))
    ((instr body)   (list $1 $2)))
    (instr 
    ((names Lassign expr Lsc) (Passign $1 $3 $2-start-pos)))
    (expr
     ((Lvar Lopar args Lcpar)    (Pcall $1 $3 $1-start-pos))
     ((expr Land expr) (Pcall '%and (list $1 $3) $2-start-pos))
     ((expr Lor expr)  (Pcall '%or  (list $1 $3) $2-start-pos))
     ((expr Lxor expr) (Pcall '%xor (list $1 $3) $2-start-pos))
     ((Lnot expr)      (Pcall '%not (list $2) $1-start-pos))
     ((arg)            $1))
    (args
     ((arg)      (list $1))
     ((arg Lco args) (list $1 $3)))
    (arg
     ((Lvar) (Pident $1 $1-start-pos))
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

