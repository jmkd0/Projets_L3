#lang racket/base

(require racket/match
         "ast.rkt"
         "baselib.rkt"
         "helper.rkt")

(provide compile)

;;;
;;; local helper functions
;;;

(define (stack-push regs)
  (append (list (Addi 'sp 'sp (* -4 (length regs))))
          (let loop ([regs regs])
            (if (null? regs) (list)
                (cons (Sw (car regs) (Mem 'sp (* 4 (- (length regs) 1))))
                      (loop (cdr regs)))))))

(define (stack-pop regs)
  (append (let loop ([regs regs])
            (if (null? regs) (list)
                (cons (Lw (car regs) (Mem 'sp (* 4 (- (length regs) 1))))
                      (loop (cdr regs)))))
          (list (Addi 'sp 'sp (* 4 (length regs))))))

;;;
;;; compiler
;;;

(define (compile-and-push expr env)
  (append (compile-expr expr env)
          (stack-push (list 'v0))))

(define (compile-expr expr env)
  (match expr
    [(Nil)
     (list (Li 'v0 0))]
    [(Num n)
     (list (Li 'v0 n))]
    [(Data l)
     (list (La 'v0 (Lbl l)))]
    [(Call f as)
     (append
      (apply append (map (lambda (a) (compile-and-push a env)) as))
      (hash-ref env f)
      (list (Addi 'sp 'sp (* 4 (length as)))))]))

(define (compile-prog prog env)
  (compile-expr prog env))

(define (compile ast)
  (Mips
   (append (list (Asciiz 'newline "\\n"))
           (map (lambda (s) (Asciiz (car s) (cdr s))) (cdr ast)))
   (append *baselib-implem*
           (list (Label 'main)
                 (Addi 'sp 'sp -4)
                 (Sw 'ra (Mem 'sp 0)))
           (compile-prog (car ast) *baselib*)
           (list (La 'a0 (Lbl 'newline))
                 (Li 'v0 PRINT_STRING)
                 (Syscall)
                 (Lw 'ra (Mem 'sp 0))
                 (Addi 'sp 'sp 4)
                 (Jr 'ra)))))
