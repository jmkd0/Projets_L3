#! /usr/bin/env racket

#lang racket/base

(require "parser.rkt"
         "typechecker.rkt"
         "call-simplifier.rkt"
         "compiler.rkt"
         "mips-optimiser.rkt"
         "mips-printer.rkt"
         racket/string)

(define argv (current-command-line-arguments))
(when (not (equal? (vector-length argv) 1))
  (eprintf "Usage: piton.rkt <source.py>\n")
  (exit 1))

(define in-filename (vector-ref argv 0))
(define in (open-input-file in-filename))
(port-count-lines! in)
(define ast (parse in))
(close-input-port in)


(define typechecked-ast (typecheck ast))
(define simplified-ast (simplify-calls typechecked-ast))
(define mips (compile simplified-ast))
(define optimised-mips (optimise-mips mips))
(define out-filename
  (let ([basename (string-trim in-filename ".py" #:right? #t)])
    (string-append basename ".s")))
(define out (open-output-file out-filename #:exists 'replace))
(print-mips optimised-mips out)
(close-output-port out)

(exit 0)
