#lang racket/base

(provide (all-defined-out))

;; Instructions MIPS
(struct Move (rd rs))      ;; move $~a, $~a\n
(struct Li (r i))          ;; li $~a, ~a\n
(struct La (r a))          ;; la $~a, ~a\n
(struct Addi (rd rs i))    ;; addi $~a, $~a, ~a\n
(struct Add (rd rs1 rs2))  ;; add $~a, $~a, $~a\n
(struct Sub (rd rs1 rs2))  ;; sub $~a, $~a, $~a\n
(struct Mul (rd rs1 rs2))  ;; mul $~a, $~a, $~a\n
(struct Div (rd rs1 rs2))  ;; div $~a, $~a, $~a\n
(struct Lo (rd))           ;; mflo $~a\n
(struct Seq (rd rs1 rs2))  ;; seq $~a, $~a, $~a\n
(struct Sne (rd rs1 rs2))  ;; sne $~a, $~a, $~a\n
(struct Sgt (rd rs1 rs2))  ;; sgt $~a, $~a, $~a\n
(struct Slt (rd rs1 rs2))  ;; slt $~a, $~a, $~a\n
(struct Sge (rd rs1 rs2))  ;; sge $~a, $~a, $~a\n
(struct Sle (rd rs1 rs2))  ;; sle $~a, $~a, $~a\n
(struct And (rd rs1 rs2))  ;; and $~a, $~a, $~a\n
(struct Or  (rd rs1 rs2))  ;; or $~a, $~a, $~a\n
(struct B (l))             ;; b ~a\n
(struct Beqz (rs l))       ;; beqz $~a, ~a\n
(struct Bnez (rs l))       ;; bnez $~a, ~a\n
(struct Sw (r loc))        ;; sw $~a, ~a\n
(struct Lw (r loc))        ;; lw $~a, ~a\n
(struct Syscall ())        ;; syscall\n
(struct Jr (r))            ;; jr $~a\n
(struct Label (l))         ;; \t~a:\n

;; addresses
(struct Lbl (l))   ;; label (souvent présent dans .data)
(struct Mem (b r)) ;; emplacement mémoire à l'adresse b + valeur du registre r
