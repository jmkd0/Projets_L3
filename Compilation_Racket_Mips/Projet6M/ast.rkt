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