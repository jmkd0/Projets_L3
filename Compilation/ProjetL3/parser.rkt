#lang racket/base
(require parser-tools/yacc
         parser-tools/lex 
         "lexer.rkt"
         "ast.rkt")

(provide parse)


(define parse-prog
    (parser 
    (src-pos)
    (tokens keywords-and-operators values-and-names)
    
    (grammar 
    (prog 
    [(block)    (list $1)]
    [(block prog)   (cons $1 $2)])
    (block 
    ((Ldef Lvar Lopar names Lcpar Lopar names Lcpar Loacc body Lcacc) 
        (Pblock $2 $4 $7 $10 $11-end-pos)))
    (names 
    ((Lvar)   (list $1))
    ((Lvar Lco names) (list $1 $3)))
    (body 
    ((instr)        (list $1))
    ((instr body)   (list $1 $2)))
    (instr 
    ((names Lassign expr Lsc) (Passign $1 $3 $2-start-pos)))  
    (expr 
    ((arg)            $1)
    ((Lvar Lopar args Lcpar)    (Pcall $1 $3 $1-start-pos))
    ((expr Ladd expr) (Pcall '%add (list $1 $3) $2-start-pos))
    ((expr Lsub expr) (Pcall '%sub (list $1 $3) $2-start-pos))
    ((expr Lmul expr) (Pcall '%mul (list $1 $3) $2-start-pos))
    ((expr Ldiv expr) (Pcall '%div (list $1 $3) $2-start-pos))
    ((expr Land expr) (Pcall '%and (list $1 $3) $2-start-pos))
    ((expr Lor expr)  (Pcall '%not (list $1 $3) $2-start-pos))
    ((expr Lxor expr) (Pcall '%xor (list $1 $3) $2-start-pos))
    ((Lnot expr)      (Pcall '%not (list $2) $1-start-pos)))
    (args
      ((arg)      (list $1))
      ((arg Lco args) (list $1 $3)))
    (arg
    ((Lnum)      (Pnum $1 $1-start-pos))
    ((Lsub Lnum) (Pnum (- $2) $1-start-pos))
    ((Lvar)      (Pvar $1 $1-start-pos))
    ((Lbool)      (Pbool $1 $1-start-pos))
    ((Lopar expr Lcpar)   $2))
    
    )
    (start prog)
    (end Lend)
    (precs (left Ladd Lsub)
           (left Lmul Ldiv))
    
    (error
    (lambda (ok? name value s-pos e-pos)
      (eprintf "Parser: syntax error near ~a~a on line ~a col ~a.\n"
               name
               (if value (format " (~a)" value) "")
               (position-line s-pos)
               (position-col s-pos))
      (exit 1)))
      
      ))

      (define (parse in)
  (parse-prog (lambda () (get-token in))))

