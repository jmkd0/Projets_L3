#lang racket/base

(provide (all-defined-out))

;;;;
;;;; AST sortie du parser
;;;;
(struct Pblock (name inputs outputs body pos) #:transparent)
(struct Passign (outputs expr pos) #:transparent)
(struct Pcall (block args pos) #:transparent)
(struct Pcond (test t f pos) #:transparent)
(struct Pident (name pos) #:transparent)
(struct Pnum (val pos) #:transparent)
(struct Pbool (val pos) #:transparent)
(struct Pstr (s pos))
(struct Pnil (pos))

;; 'bool and 'num are used as base types
(struct Fun (ret args))
(struct Pair (t)       #:transparent)
;;;;
;;;; AST après analyse sémantique
;;;;

;; un programme est une liste de Block
;; un Block est une "fonction"
;; dans un Block, body est une liste d'instructions
;; une instructions ne peut être qu'un Assign
;; dans un Assign, expr est une expression
;; une expression est soit un Call, soit une Var, soit un Bool
;; dans un Call, args est une liste d'expressions

(struct Block (name inputs outputs body) #:transparent)
(struct Assign (outputs expr) #:transparent)
(struct Call (block args) #:transparent)
(struct Cond (test yes no) #:transparent)
(struct Var (name) #:transparent)
(struct Num (val) #:transparent)
(struct Bool (val) #:transparent)
(struct Str (s))
(struct Nil ())
(struct Data (l))


;;; MIPS
(struct Mips (data text))

; instructions
(struct Asciiz (lbl str))
(struct Label (lbl))
(struct Li (dst imm))
(struct La (dst loc))
(struct Addi (dst reg imm))
(struct Add (dst rg1 rg2))
(struct Sw (reg loc))
(struct Lw (reg loc))
(struct Move (dst reg))
(struct Syscall ())
(struct Jal (loc))
(struct Jr (reg))

; locations
(struct Mem (reg offset))
(struct Lbl (name))

; contants
(define PRINT_INT    1)
(define PRINT_STRING 4)
(define SBRK         9)
