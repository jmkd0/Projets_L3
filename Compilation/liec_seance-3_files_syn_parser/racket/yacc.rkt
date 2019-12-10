#lang racket/base

(require parser-tools/yacc
         racket/port
         "lexer.rkt")

(struct And (a b) #:transparent)
(struct Or  (a b) #:transparent)
(struct Not (v)   #:transparent)
(struct Bit (v)   #:transparent)

(define parse1
  ;; parser suivant la grammaire non-ambigüe du slide 15
  (parser
   (tokens operators bits)
   (grammar
    (expr
     ((expr Lor conj)    (Or $1 $3))
     ((conj)             $1))
    (conj
     ((conj Land term)   (And $1 $3))
     ((term)             $1))
    (term
     ((Lopar expr Lcpar) $2)
     ((Lnot term)        (Not $2))
     ((bit)              $1))
    (bit
     ((Lbool)           (Bit $1))))
   (start expr)
   (end Lend)
   (debug "yacc1.dbg")
   (error (lambda (ok? name value)
            (error (if value value 'Error)
                   (if ok? "error" "invalid token"))))))
(define parse2
  ;; parser suivant la grammaire plus simple mais ambigüe du slide 13,
  ;; corrigé avec des priorités données avec precs
  (parser
   (tokens operators bits)
   (grammar
    (expr
     ((expr Lor expr)   (Or $1 $3))
     ((expr Land expr)  (And $1 $3))
     ((Lopar expr Lcpar) $2)
     ((Lnot expr)       (Not $2))
     ((Lbool)           (Bit $1))))
   (start expr)
   (end Lend)

   ;; commenter la ligne ci-dessous pour voir apparaître des conflits
   ;; shift/reduce :
   (precs (left Lor) (left Land) (right Lnot))

   (debug "yacc2.dbg")
   (error (lambda (ok? name value)
            (error (if value value 'Error)
                   (if ok? "error" "invalid token"))))))

(define argv (current-command-line-arguments))
(cond
  ((= (vector-length argv) 1)
   (define in (open-input-string (vector-ref argv 0)))
   (write (parse1 (lambda () (token in))))
   (newline))
  (else
   (eprintf "Usage: racket yacc.rkt \"string\"\n")
   (exit 1)))
