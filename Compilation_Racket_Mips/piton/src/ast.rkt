#lang racket/base

(provide (all-defined-out))

;; Number literal
(struct num (val) #:transparent)
;; String literal
(struct str (val) #:transparent)
;; Constant
(struct const (val) #:transparent)
;; Name
(struct name (id) #:transparent)
;; Subscript
(struct subscript (value index) #:transparent)
;; Binnary operation
(struct binoper (op lhs rhs) #:transparent)
;; Unary operation
(struct unoper (op operand) #:transparent)
;; Call
(struct call (callee args) #:transparent)

;; Variable declaration
(struct decl (id type val) #:transparent)
;; Assignation
(struct assign (target val) #:transparent)
;; Return
(struct return (value) #:transparent)
;; If
(struct if (test body else-body) #:transparent)
;; While
(struct while (test body) #:transparent)

;; Function definition
(struct funcdef (id return-type params body) #:transparent)
;; Function parameter
(struct param (id type) #:transparent)

;; Block (internal only)
;; use by call-simplifier to insert multiple statements in test condition of if or while
(struct block (body) #:transparent)

;; With position
(struct pos-num num (pos))
(struct pos-str str (pos))
(struct pos-const const (pos))
(struct pos-name name (pos))
(struct pos-subscript subscript (pos))
(struct pos-binoper binoper (pos))
(struct pos-unoper unoper (pos))
(struct pos-call call (pos))
(struct pos-decl decl (pos))
(struct pos-assign assign (pos))
(struct pos-if if (pos))
(struct pos-while while (pos))
(struct pos-return return (pos))
(struct pos-funcdef funcdef (pos))
(struct pos-param param (pos))
