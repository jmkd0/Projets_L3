#lang racket/base

(require racket/match
         racket/list)
(provide (all-defined-out))

(struct comment (val) #:transparent)

(struct data-section () #:transparent)
;; Data instructions
(struct word (label num) #:transparent)
(struct asciiz (label string) #:transparent)

(struct text-section () #:transparent)
;; Text instructions
(struct globl (name) #:transparent)
(struct label (name) #:transparent)
(struct li (dest src) #:transparent)
(struct move (dest src) #:transparent)
(struct la (dest src) #:transparent)
; operations
(struct add (dest lhs rhs) #:transparent)
(struct sub (dest lhs rhs) #:transparent)
(struct mul (dest lhs rhs) #:transparent)
(struct div (dest lhs rhs) #:transparent)
(struct addi (dest lhs rhs) #:transparent)
; logical
(struct land (dest lhs rhs) #:transparent)
(struct lor (dest lhs rhs) #:transparent)
; comparison
(struct seq (dest lhs rhs) #:transparent)
(struct sne (dest lhs rhs) #:transparent)
(struct sgt (dest lhs rhs) #:transparent)
(struct slt (dest lhs rhs) #:transparent)
(struct sge (dest lhs rhs) #:transparent)
(struct sle (dest lhs rhs) #:transparent)
; memory
(struct lw (dest src) #:transparent)
(struct lb (dest src) #:transparent)
(struct sw (src dest) #:transparent)
(struct sb (src dest) #:transparent)
; branch/jump
(struct b (label) #:transparent)
(struct beq (lhs rhs label) #:transparent)
(struct beqz (reg label) #:transparent)
(struct jal (label) #:transparent)
(struct jalr (reg) #:transparent)
(struct jr (reg) #:transparent)
(struct syscall () #:transparent)
(struct nop () #:transparent)

;; <return> #t if <instr> belongs to data section
(define (data-instr? instr)
  (match instr
    [(? word?) #t]
    [(? asciiz?) #t]
    [_ #f]))

;; Locations
(struct reg (name) #:transparent)
(struct mem (offset reg) #:transparent)
(struct outer-mem (level-offset stack-offset) #:transparent)
; label can be used both as instruction and value

;; Register shortcuts
(define $sp (reg "sp"))
(define $ra (reg "ra"))
(define $v0 (reg "v0"))
(define $a0 (reg "a0"))
(define $a1 (reg "a1"))
(define $a2 (reg "a2"))
(define $a3 (reg "a3"))
(define $t0 (reg "t0"))
(define $t1 (reg "t1"))
(define $t2 (reg "t2"))
(define $t3 (reg "t3"))
(define $t4 (reg "t4"))
(define $t5 (reg "t5"))
(define $t6 (reg "t6"))
(define $t7 (reg "t7"))
(define $t8 (reg "t8"))
(define $t9 (reg "t9"))
(define $zero (reg "zero"))

;; Syscall constants
(define syscall-print-int 1)
(define syscall-print-str 4)
(define syscall-read-str 8)
(define syscall-sbrk 9)
(define syscall-exit 10)
(define syscall-print-char 11)
