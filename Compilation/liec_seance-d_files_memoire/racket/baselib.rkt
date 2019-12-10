#lang racket/base

(require "ast.rkt")

(provide (all-defined-out))

(define *baselib-types*
  (make-immutable-hash
   (list (cons '%add (Fun 'num (list 'num 'num)))
         (cons 'print_num (Fun 'void (list 'num)))
         (cons 'print_str (Fun 'void (list 'str)))
         (cons 'pair (Fun (Pair 'num) (list 'num (Pair 'num))))
         (cons 'head (Fun 'num (list (Pair 'num))))
         (cons 'tail (Fun (Pair 'num) (list (Pair 'num)))))))

(define *baselib*
  (make-immutable-hash
   (list (cons '%add
               (list (Lw 't0 (Mem 'sp 4))
                     (Lw 't1 (Mem 'sp 0))
                     (Add 'v0 't0 't1)))
         (cons 'print_num
               (list (Lw 'a0 (Mem 'sp 0))
                     (Li 'v0 PRINT_INT)
                     (Syscall)))
         (cons 'print_str
               (list (Lw 'a0 (Mem 'sp 0))
                     (Li 'v0 PRINT_STRING)
                     (Syscall)))
         (cons 'pair
               (list (Jal (Lbl "_pair"))))
         (cons 'head
               (list (Lw 't0 (Mem 'sp 0))
                     (Lw 'v0 (Mem 't0 -4))))
         (cons 'tail
               (list (Lw 't0 (Mem 'sp 0))
                     (Lw 'v0 (Mem 't0 0)))))))

(define *baselib-implem*
  (list (Label "_pair")
        (Li 'a0 8)
        (Li 'v0 SBRK)
        (Syscall)
        (Lw 't0 (Mem 'sp 4))
        (Sw 't0 (Mem 'v0 -4))
        (Lw 't0 (Mem 'sp 0))
        (Sw 't0 (Mem 'v0 0))
        (Jr 'ra)))
