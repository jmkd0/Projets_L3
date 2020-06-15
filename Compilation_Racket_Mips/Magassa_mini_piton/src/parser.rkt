#lang racket/base

(require parser-tools/yacc
         "lexer.rkt"
         "ast.rkt")

(provide liec-parser)


(require (for-syntax racket/base))
(require compatibility/defmacro)
(defmacro sp n
  (string->symbol (string-append "$" (number->string (car n)) "-start-pos")))

(define parse
  (parser
   (src-pos)
   (tokens keywords operators punctuations atoms)
   (start prog)
   (end Leof)

   (grammar
    (prog
     ((definition prog)  (cons $1 $2))
     ((definition)       (list $1)))

    (definition
     ((type Lident Lassign sexpr Lsc)                           (Pvardef $2 $4 $1 (sp 2)))
     ((Lident Lassign sexpr Lsc)                                (Pvar    $1 $3 (sp 2))) 
     ((type Lident Lopar argtypes Lcol fargs Lcpar fblock)      (Pfundef #f $2 $6 $8 (Fun $1 $4) (sp 2)))
     ((Lrec type Lident Lopar argtypes Lcol fargs Lcpar fblock) (Pfundef #t $3 $7 $9 (Fun $2 $5) (sp 3))))
     ;; Not the right structure for a function in C
     
    (type
     ((type Llist) (Lst $1))
     ((Ltype)      $1))

    (argtypes
     ((type Lcom argtypes) (cons $1 $3))
     ((type)               (list $1)))

    (fargs
     ((Lident Lcom fargs) (cons (Pident $1 (sp 1)) $3))
     ((Lident)            (list (Pident $1 (sp 1))))
     ((Lnil)              (list (Pident 'nil (sp 1)))))

    (fblock
     ((Locbra exprs Lreturn sexpr Lsc Lccbra) (Pfunblock $2 $4 (sp 1))))

    (expr
     ((definition)          $1)
     ((funcall)             $1)     
     ((test)                $1)
     ((loop)                $1)
     ((Lopar expr Lcpar)    $2)
     ((Locbra exprs Lccbra) (Pblock $2 (sp 1))))

    (exprs
     ((expr exprs) (cons $1 $2))
     ((expr)       (list $1)))

    
    (loop
     ((Lwhile Lopar sexpr Lcpar expr) (Ploop $3 $5 (sp 1))))

    (test
     ((Lif Lopar sexpr Lcpar expr Lelse expr) (Pcond $3 $5 $7 (sp 1)))) ;; TODO : if/else if/else - with option?

    (funcall
     ((Lident Lopar args Lcpar Lsc) (Pcall $1 $3 (sp 1))))

    (args
     ((sexpr Lcom args) (cons $1 $3))
     ((sexpr)           (list $1)))

    (sexpr ;; single-expr
     ((atom)              $1)
     ((funcall)           $1)
     ((operation)         $1)
     ((Lopar sexpr Lcpar) $2))

    (operation
     ((sexpr Ladd sexpr) (Pcall '+ (list $1 $3) (sp 1)))
     ((sexpr Lsub sexpr) (Pcall '- (list $1 $3) (sp 1)))
     ((sexpr Lmul sexpr) (Pcall '* (list $1 $3) (sp 1)))
     ((sexpr Ldiv sexpr) (Pcall '/ (list $1 $3) (sp 1)))
     ((sexpr Lmod sexpr) (Pcall '% (list $1 $3) (sp 1)))

     ((sexpr Leq sexpr)  (Pcall '== (list $1 $3) (sp 1)))
     ((sexpr Lneq sexpr) (Pcall '!= (list $1 $3) (sp 1)))
     ((sexpr Llt sexpr)  (Pcall '<  (list $1 $3) (sp 1)))
     ((sexpr Lgt sexpr)  (Pcall '>  (list $1 $3) (sp 1)))
     ((sexpr Llte sexpr) (Pcall '<= (list $1 $3) (sp 1)))
     ((sexpr Lgte sexpr) (Pcall '>= (list $1 $3) (sp 1)))

     ((sexpr Land sexpr) (Pcall '&& (list $1 $3) (sp 1)))
     ((sexpr Lor sexpr)  (Pcall '|| (list $1 $3) (sp 1)))
     ((Lnot sexpr)       (Pcall '!  (list $2) (sp 1))))

    (atom
     ((Lnil)               (Pconst 'nil '() (sp 1)))
     ((Lbool)              (Pconst 'bool $1 (sp 1)))
     ((Lnum)               (Pconst 'int $1 (sp 1)))
     ((Lstr)               (Pconst 'str $1 (sp 1)))
     ((Lident)             (Pident $1 (sp 1)))
     ((Locbra elem Lccbra) $2))

    (elem
     ((sexpr Lcom elem) (Pcall 'cons (list $1 $3) (sp 1)))
     ((sexpr)           (Pcall 'cons (list $1 (Pconst 'nil '() #f)) (sp 1)))
     (()                (Pconst 'nil '() #f)))

   )

   (precs (left Lor)
          (left Lxor)
          (left Land)
          (right Lnot)

          (left Leq)
          (left Lneq)
          (left Llt)
          (left Lgt)
          (left Llte)
          (left Lgte)

          (left Lmod)
          (left Ladd)
          (left Lsub)
          (left Lmul)
          (left Ldiv))

   (debug "yacc.dbg")
   (error
    (lambda (ok? name value s-pos e-pos)
      (eprintf "Parser: ~a: ~a~a on line ~a col ~a.\n"
               (substring (symbol->string name) 1)
               (if ok? "syntax error" "unexpected token")
               (if value (format " near '~a'" value) "")
               (position-line s-pos)
               (position-col s-pos))
      (exit 1)))))

(define (liec-parser in)
  (parse (lambda () (liec-lexer in))))
