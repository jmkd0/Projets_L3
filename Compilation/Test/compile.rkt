#lang racket/base
(require racket/match
         "ast.rkt"
         "mips.rkt"
         "helper.rkt")

(provide compile mips-emit)
;;sans mips
;;(define (compile-prog prog)
;;  (match prog
;;   [(Num n)]))
;;(define (compile ast)
;;  (compile-prog ast))



;;intervention de mips
(define (compile-prog prog)
  (match prog
    [(Num n) (list (Li 'v0 n))]))
(define (compile ast)
  (ASM
   (list (Asciiz 'newline "\\n"))
   (append
    (list
     (Label 'main)
     (Addi 'sp 'sp -4)
     (Sw 'ra (Addr 'sp 0)))
    (compile-prog ast)
    (list
     (Move 'a0 'v0)
     (Li 'v0 print_int)
     (Syscall)
     (La 'a0 (Lbl 'newline))
     (Lw 'ra (Addr 'sp 0))
     (Addi 'sp 'sp 4)
     (Jr 'ra)))))

(define (mips-emit asm)
  (printf " .data\n")
  (emit-data (ASM-data asm))
  (printf " .text\n .global main\n")
  (emit-text (ASM-text asm)))

(define (emit-dinstr instr)
  (match instr
    [(Asciiz ns) (printf "~a: .acsiiz \"~a\"\n" n s)]))

(define (emit-data data)
  (for-each print-dinstr data)
  (printf "\n"))
 ;; (printf "newline: .acsiiz \"\n\"\n"))

(define (fmt-addr addr)
  (match addr
    [(Label n) (format "~a" n)]
    [(Addr r o) (format "~a($~a)" o r)]))

(define (print-instr instr)
  (match instr
    [(Label l) (printf "~a:\n" l)]
    [(Li d i)  (print " li $~a, ~a\n" d i)]
    [(La d a)  (print " la $~a, ~a\n" d (fmt-addr a))]
    [(Addr d r i)  (print " addi $~a, $~a, ~a\n" d r i)]
    [(Sw r a)  (print " sw $~a, ~a\n" r (fmt-addr a))]
    [(Sw r a)  (print " sw $~a, ~a\n" r (fmt-addr a))]
         

