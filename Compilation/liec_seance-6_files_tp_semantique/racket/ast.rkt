#lang racket/base

(provide (all-defined-out))

;; Sortie du parser
(struct Passign (var expr pos) #:transparent)
(struct Pcond (test t f pos) #:transparent)
(struct Pcall (func args pos) #:transparent)
(struct Pnum (val pos) #:transparent)
(struct Pbool (val pos) #:transparent)
(struct Pvar (name pos) #:transparent)

;; AST
(struct Assign (var expr) #:transparent)
(struct Cond (test yes no) #:transparent)
(struct Call (func args) #:transparent)
(struct Num (val) #:transparent)
(struct Bool (val) #:transparent)
(struct Var (name) #:transparent)
