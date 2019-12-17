#lang racket/base
(provide (all-defined-out))

(struct Pblock (name inputs outputs body  pos)#:transparent)
(struct Pcall(func args pos)#:transparent)
(struct Passign(vars expr pos)#:transparent)
(struct Pvar (var pos)#:transparent)
(struct Pnum (val pos)#:transparent)
(struct Pbool (val pos)#:transparent)

(struct Block (name inputs outputs body)#:transparent)
(struct Call(func args)#:transparent)
(struct Assign (var expr)#:transparent)
(struct Var (var)#:transparent)
(struct Num (val)#:transparent)
(struct Bool (val) #:transparent)


