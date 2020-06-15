#lang racket/base

(require racket/match
         racket/list
         "mips.rkt")
(provide print-mips)

(define (print-mips instrs out)
  (for ([instr instrs])
    (displayln (instr->string instr) out)))

(define (instr->string instr)
  (match instr
    [(comment val)
     (string-append "# " val)]
    ;; Data
    [(data-section)
     ".data"]
    [(word label num)
     (format "~a: .word ~a" (val->string label) num)]
    [(asciiz label string)
     (format "~a: .asciiz ~s" (val->string label) string)]
    ;; Text
    [(text-section)
     ".text"]
    [(globl name)
     (format ".globl ~a" name)]
    [(label name)
     (format "~a:" name)]
    [(li dest src)
     (format "li ~a ~a" (val->string dest) (val->string src))]
    [(move dest src)
     (format "move ~a ~a" (val->string dest) (val->string src))]
    [(la dest src)
     (format "la ~a ~a" (val->string dest) (val->string src))]
    [(add dest lhs rhs)
     (format "add ~a ~a ~a" (val->string dest) (val->string lhs) (val->string rhs))]
    [(sub dest lhs rhs)
     (format "sub ~a ~a ~a" (val->string dest) (val->string lhs) (val->string rhs))]
    [(mul dest lhs rhs)
     (format "mul ~a ~a ~a" (val->string dest) (val->string lhs) (val->string rhs))]
    [(div dest lhs rhs)
     (format "div ~a ~a ~a" (val->string dest) (val->string lhs) (val->string rhs))]
    [(addi dest lhs rhs)
     (format "addi ~a ~a ~a" (val->string dest) (val->string lhs) (val->string rhs))]
    [(land dest lhs rhs)
     (format "and ~a ~a ~a" (val->string dest) (val->string lhs) (val->string rhs))]
    [(lor dest lhs rhs)
     (format "or ~a ~a ~a" (val->string dest) (val->string lhs) (val->string rhs))]
    [(seq dest lhs rhs)
     (format "seq ~a ~a ~a" (val->string dest) (val->string lhs) (val->string rhs))]
    [(sne dest lhs rhs)
     (format "sne ~a ~a ~a" (val->string dest) (val->string lhs) (val->string rhs))]
    [(sgt dest lhs rhs)
     (format "sgt ~a ~a ~a" (val->string dest) (val->string lhs) (val->string rhs))]
    [(slt dest lhs rhs)
     (format "slt ~a ~a ~a" (val->string dest) (val->string lhs) (val->string rhs))]
    [(sge dest lhs rhs)
     (format "sge ~a ~a ~a" (val->string dest) (val->string lhs) (val->string rhs))]
    [(sle dest lhs rhs)
     (format "sle ~a ~a ~a" (val->string dest) (val->string lhs) (val->string rhs))]
    [(lw dest src)
     (format "lw ~a ~a" (val->string dest) (val->string src))]
    [(lb dest src)
     (format "lb ~a ~a" (val->string dest) (val->string src))]
    [(sw dest src)
     (format "sw ~a ~a" (val->string dest) (val->string src))]
    [(sb dest src)
     (format "sb ~a ~a" (val->string dest) (val->string src))]
    [(beq lhs rhs label)
     (format "beq ~a ~a ~a" (val->string lhs) (val->string rhs) (val->string label))]
    [(beqz reg label)
     (format "beqz ~a ~a" (val->string reg) (val->string label))]
    [(b label)
     (format "b ~a" (val->string label))]
    [(jal label)
     (format "jal ~a" (val->string label))]
    [(jalr reg)
     (format "jalr ~a" (val->string reg))]
    [(jr reg)
     (format "jr ~a" (val->string reg))]
    [(syscall)
     "syscall"]
    [(nop)
     "nop"]))

(define (val->string val)
  (match val
    [(reg name)
     (format "$~a" name)]
    [(mem offset reg)
     (format "~a(~a)" offset (val->string reg))]
    [(label name)
     name]
    [(? number?)
     (number->string val)]))
