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
     ((Llet Lident names Lrarr names Lwhere body Ldot)
      (Pblock $2 $3 $5 $7 $8-end-pos)))
    (names
     ((Lident)       (list $1))
     ((Lident names) (cons $1 $2)))
    (body
     ((instr)          (list $1))
     ((instr Lsc body) (cons $1 $3)))
    (instr
     ((names Llarr expr) (Passign $1 $3 $2-start-pos)))
    (expr
     ((Lident args)    (Pcall $1 $2 $1-start-pos))
     ((expr Land expr) (Pcall '%and (list $1 $3) $2-start-pos))
     ((expr Lor expr)  (Pcall '%or  (list $1 $3) $2-start-pos))
     ((expr Lxor expr) (Pcall '%xor (list $1 $3) $2-start-pos))
     ((Lnot expr)      (Pcall '%not (list $2) $1-start-pos))
     ((arg)            $1))
    (args
     ((arg)      (list $1))
     ((arg args) (cons $1 $2)))
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
