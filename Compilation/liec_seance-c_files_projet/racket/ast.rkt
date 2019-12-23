#lang racket/base

(provide (all-defined-out))

;;; parsed syntax
(struct Pnum (n pos)          #:transparent)
(struct Pcall (func args pos) #:transparent)

;;; types
(struct Fun (ret args))

;;; AST
(struct Num (n)          #:transparent)
(struct Call (func args) #:transparent)


;;; MIPS
(struct Mips (data text) #:transparent)

; instructions
(struct Asciiz (lbl str)   #:transparent)
(struct Label (lbl)        #:transparent)
(struct Li (dst imm)       #:transparent)
(struct La (dst loc)       #:transparent)
(struct Addi (dst reg imm) #:transparent)
(struct Add (dst rg1 rg2)  #:transparent)
(struct Sw (reg loc)       #:transparent)
(struct Lw (reg loc)       #:transparent)
(struct Move (dst reg)     #:transparent)
(struct Syscall ()         #:transparent)
(struct Jr (reg)           #:transparent)

; locations
(struct Mem (reg offset) #:transparent)
(struct Lbl (name)       #:transparent)

; contants
(define PRINT_INT    1)
(define PRINT_STRING 4)
