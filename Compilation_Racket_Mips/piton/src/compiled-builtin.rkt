#lang racket/base

(require racket/list
         "mips.rkt"
         "mips-helper.rkt")
(provide (all-defined-out))

;; Read string
(define (input)
  ; prepare while labels
  (define while-id (symbol->string (gensym)))
  (define while-label (label (string-append "while_" while-id)))
  (define endwhile-label (label (string-append "endwhile_" while-id)))
  (list (lw $a0 (mem (* -4 1) $sp))
        ; print prompt
        (li $v0 syscall-print-str)
        (syscall)
        ; alloc new string
        (li $a0 256) ; max input length
        (li $v0 syscall-sbrk)
        (syscall)
        ; read input into new stringapply
        (move $a0 $v0)
        (li $a1 256) ; max input length
        (li $v0 syscall-read-str)
        (syscall)
        ; remove trailing \n
        ; saving string in $v0 while using $a0 as pointer
        (move $v0 $a0)
        while-label
        (lb $t0 (mem 0 $a0)) ; char
        (beq $t0 #xA endwhile-label) ; stop at \n
        (addi $a0 $a0 1) ; increment pointer
        (b while-label)
        endwhile-label
        (sb $zero (mem 0 $a0)) ; replace \n with \0
        (jr $ra)))

;; Print boolean
(define (print-bool)
  ; prepare if labels
  (define if-id (symbol->string (gensym)))
  (define if-label (label (string-append "if_" if-id)))
  (define else-label (label (string-append "else_" if-id)))
  (define endif-label (label (string-append "endif_" if-id)))
  ; prepare string labels
  (define true-id (symbol->string (gensym)))
  (define true-label (label (string-append "str_" true-id)))
  (define false-id (symbol->string (gensym)))
  (define false-label (label (string-append "str_" false-id)))
  (list (lw $a0 (mem (* -4 1) $sp))
        (li $v0 syscall-print-str)
        if-label
        (beqz $a0 else-label)
        (asciiz true-label "True")
        (la $a0 true-label)
        (b endif-label)
        else-label
        (asciiz false-label "False")
        (la $a0 false-label)
        endif-label
        (syscall)
        (li $a0 #xA) ; newline
        (li $v0 syscall-print-char)
        (syscall)
        (jr $ra)))

;; Divide integers
(define (div-ints)
  ; prepare error labels
  (define err-id (symbol->string (gensym)))
  (define err-label (label (string-append "err_" err-id)))
  (define msg-id (symbol->string (gensym)))
  (define msg-label (label (string-append "str_" msg-id)))
  (list (lw $a0 (mem (* -4 1) $sp))
        (lw $a1 (mem (* -4 2) $sp))
        (beqz $a1 err-label)
        (div $v0 $a0 $a1)
        (jr $ra)
        ; error handling
        err-label
        (asciiz msg-label "ZeroDivisionError: division by zero")
        (la $a0 msg-label)
        (li $v0 syscall-print-str)
        (syscall)
        (li $a0 #xA) ; newline
        (li $v0 syscall-print-char)
        (syscall)
        (li $v0 syscall-exit)
        (syscall)))

;; Strings equal
(define (eq-strs [test-for-equality? #t])
  ; prepare while labels
  (define while-id (symbol->string (gensym)))
  (define while-label (label (string-append "while_" while-id)))
  (define endwhile-label (label (string-append "endwhile_" while-id)))
  ; prepare if labels
  (define if-id (symbol->string (gensym)))
  (define if-label (label (string-append "if_" if-id)))
  (define endif-label (label (string-append "endif_" if-id)))
  (list (lw $a0 (mem (* -4 1) $sp)) ; using $a0 as pointer
        (lw $a1 (mem (* -4 2) $sp)) ; using $a1 as pointer
        while-label
        (lb $t0 (mem 0 $a0)) ; char of 1st string
        (lb $t1 (mem 0 $a1)) ; char of 2d string
        if-label
        (beq $t0 $t1 endif-label)
        (li $v0 (if test-for-equality? 0 1)) ; found different char
        (jr $ra)
        endif-label
        (beqz $t0 endwhile-label) ; stop at \0
        (beqz $t1 endwhile-label) ; stop at \0
        ; increment pointers
        (addi $a0 $a0 1)
        (addi $a1 $a1 1)
        (b while-label)
        endwhile-label
        (li $v0 (if test-for-equality? 1 0)) ; no different char found
        (jr $ra)))

;; Strings not equal
(define neq-strs (lambda () (eq-strs #f)))

;; String char at index (subscript access)
;; first argument: string, second argument: index
(define (char-at-index)
  ; prepare error labels
  (define err-id (symbol->string (gensym)))
  (define err-label (label (string-append "err_" err-id)))
  (define msg-id (symbol->string (gensym)))
  (define msg-label (label (string-append "str_" msg-id)))
  ; prepare while labels
  (define while-id (symbol->string (gensym)))
  (define while-label (label (string-append "while_" while-id)))
  (define endwhile-label (label (string-append "endwhile_" while-id)))
  (list (lw $a0 (mem (* -4 1) $sp)) ; using $a0 as pointer
        (lw $a1 (mem (* -4 2) $sp)) ; index
        (li $t0 0) ; counter
        while-label
        (lb $t1 (mem 0 $a0)) ; char
        ; error if \0 was found
        (beqz $t1 err-label)
        ; stop when counter == index
        (beq $t0 $a1 endwhile-label)
        ; increment pointer and counter
        (addi $a0 $a0 1)
        (addi $t0 $t0 1)
        (b while-label)
        endwhile-label
        ; allocate new string of length 1
        (li $a0 2) ; +1 for \0
        (li $v0 syscall-sbrk)
        (syscall) ; new address in $v0
        (sb $t1 (mem 0 $v0)) ; copy char to new address
        (sb $zero (mem 1 $v0)) ; add \0 at end
        ; new string already in $v0
        (jr $ra)
        ; error handling
        err-label
        (asciiz msg-label "IndexError: string index out of range")
        (la $a0 msg-label)
        (li $v0 syscall-print-str)
        (syscall)
        (li $a0 #xA) ; newline
        (li $v0 syscall-print-char)
        (syscall)
        (li $v0 syscall-exit)
        (syscall)))

;; String length
(define (str-len)
  (append (list (lw $a0 (mem (* -4 1) $sp)))
          (str-len-aux)
          (list (jr $ra))))

;; share code with <add-strs> because it cant call <str-len>...
(define (str-len-aux)
  ; prepare while labels
  (define while-id (symbol->string (gensym)))
  (define while-label (label (string-append "while_" while-id)))
  (define endwhile-label (label (string-append "endwhile_" while-id)))
  (list (li $v0 0) ; using $v0 as counter
        while-label
        (lb $t0 (mem 0 $a0)) ; char
        ; stop at \0
        (beqz $t0 endwhile-label)
        ; increment pointer and counter
        (addi $a0 $a0 1)
        (addi $v0 $v0 1)
        (b while-label)
        endwhile-label))

;; String negation
(define (lnot-str)
  (list (lw $a0 (mem (* -4 1) $sp))
        (lb $a0 (mem 0 $a0))
        (seq $v0 $a0 0) ; false if not empty
        (jr $ra)))

;; String to boolean
(define (str-to-bool)
  (list (lw $a0 (mem (* -4 1) $sp))
        (lb $a0 (mem 0 $a0))
        (sne $v0 $a0 0) ; false if not empty
        (jr $ra)))

;; Add strings
(define (add-strs)
  ; prepare while labels
  (define while1-id (symbol->string (gensym)))
  (define while1-label (label (string-append "while_" while1-id)))
  (define endwhile1-label (label (string-append "endwhile_" while1-id)))
  (define while2-id (symbol->string (gensym)))
  (define while2-label (label (string-append "while_" while2-id)))
  (define endwhile2-label (label (string-append "endwhile_" while2-id)))
  (append (list (lw $a0 (mem (* -4 1) $sp))) ; load 1st string from stack
          ; run str_len on 1st string
          (str-len-aux)
          (list (sw $v0 (mem (* -4 3) $sp)) ; stack 1st length
                ; call str_len on 2d string
                (lw $a0 (mem (* -4 2) $sp))) ; load 2d string from stack
          ; run str_len on 2d string
          (str-len-aux)
          (list (lw $t0 (mem (* -4 1) $sp)) ; 1st string
                (lw $t1 (mem (* -4 2) $sp)) ; 2d string
                (lw $t2 (mem (* -4 3) $sp)) ; 1st length
                (move $t3 $v0) ; 2d length

                ; allocate new length
                (add $a0 $t2 $t3) ; total length
                (addi $a0 $a0 1) ; +1 for \0
                (li $v0 syscall-sbrk)
                (syscall) ; new address in $v0
                ; copy new address to use it as pointer
                ; while preserving $v0
                (move $t4 $v0)

                ; copy 1st string to new address
                while1-label
                (lb $t5 (mem 0 $t0)) ; current char
                (beqz $t5 endwhile1-label) ; stop at \0
                ; copy char
                (sb $t5 (mem 0 $t4))
                ; increment addresses
                (addi $t0 $t0 1)
                (addi $t4 $t4 1)
                (b while1-label)
                endwhile1-label

                ; copy 2d string to new address
                while2-label
                (lb $t5 (mem 0 $t1)) ; current char
                (beqz $t5 endwhile2-label) ; stop at \0
                ; copy char
                (sb $t5 (mem 0 $t4))
                ; increment addresses
                (addi $t1 $t1 1)
                (addi $t4 $t4 1)
                (b while2-label)
                endwhile2-label

                ; add \0 at end
                (sb $zero (mem 0 $t4))

                ; new string already in $v0
                (jr $ra))))

;;; Print integer (inlined)
(define (print-int dest-loc args-vals)
  (append (move-val $a0 (first args-vals))
          (list (li $v0 syscall-print-int)
                (syscall)
                (li $a0 #xA) ; newline
                (li $v0 syscall-print-char)
                (syscall))))

;; Print string (inlined)
(define (print-str dest-loc args-vals)
  (append (move-val $a0 (first args-vals))
          (list (li $v0 syscall-print-str)
                (syscall)
                (li $a0 #xA) ; newline
                (li $v0 syscall-print-char)
                (syscall))))

;; Add integers (inlined)
(define (add-ints dest-loc args-vals)
  (apply-bininstr add dest-loc (first args-vals) (second args-vals)))
;; Substract integers (inlined)
(define (sub-ints dest-loc args-vals)
  (apply-bininstr sub dest-loc (first args-vals) (second args-vals)))

;; Multiply integers (inlined)
(define (mul-ints dest-loc args-vals)
  (apply-bininstr mul dest-loc (first args-vals) (second args-vals)))

;; Bools and (inlined)
(define (land-bools dest-loc args-vals)
  (apply-bininstr land dest-loc (first args-vals) (second args-vals)))

;; Bools or (inlined)
(define (lor-bools dest-loc args-vals)
  (apply-bininstr lor dest-loc (first args-vals) (second args-vals)))

;; Bool negation (inlined)
(define (lnot-bool dest-loc args-vals)
  (apply-bininstr seq dest-loc (first args-vals) 0))

;; Integers equal (inlined)
(define (eq-ints dest-loc args-vals)
  (apply-bininstr seq dest-loc (first args-vals) (second args-vals)))

;; Integers not equal (inlined)
(define (neq-ints dest-loc args-vals)
  (apply-bininstr sne dest-loc (first args-vals) (second args-vals)))

;; Integers greater than (inlined)
(define (gt-ints dest-loc args-vals)
  (apply-bininstr sgt dest-loc (first args-vals) (second args-vals)))

;; Integers greater than or equal (inlined)
(define (gte-ints dest-loc args-vals)
  (apply-bininstr sge dest-loc (first args-vals) (second args-vals)))

;; Integers less than (inlined)
(define (lt-ints dest-loc args-vals)
  (apply-bininstr slt dest-loc (first args-vals) (second args-vals)))

;; Integers less than or equal (inlined)
(define (lte-ints dest-loc args-vals)
  (apply-bininstr sle dest-loc (first args-vals) (second args-vals)))

;; None to boolean (inlined)
(define (none-to-bool dest-loc args-vals)
  (move-val dest-loc 0)) ; always false

;; Function to boolean (inlined)
(define (func-to-bool dest-loc args-vals)
  (move-val dest-loc 1)) ; always true

;; None negation (inlined)
(define (lnot-none dest-loc args-vals)
  (move-val dest-loc 1)) ; always false

;; Function negation (inlined)
(define (lnot-func dest-loc args-vals)
  (move-val dest-loc 0)) ; always true

(define lib
  (hash
   "input"         input
   ; print functions
   "print_bool"    print-bool
   ; integer functions
   "div_ints"      div-ints
   ; string functions
   "str_to_bool"  str-to-bool
   "lnot_str"     lnot-str
   "eq_strs"       eq-strs
   "neq_strs"      neq-strs
   "str_len"       str-len
   "char_at_index" char-at-index
   "add_strs"      add-strs))

(define lib-inlined
  (hash
   ; print functions
   "print_int"    print-int
   "print_str"    print-str
   ; integer functions
   "add_ints"     add-ints
   "sub_ints"     sub-ints
   "mul_ints"     mul-ints
   "eq_ints"      eq-ints
   "neq_ints"     neq-ints
   "gt_ints"      gt-ints
   "lt_ints"      lt-ints
   "gte_ints"     gte-ints
   "lte_ints"     lte-ints
   ; bool functions
   "land_bools"   land-bools
   "lor_bools"    lor-bools
   "lnot_bool"    lnot-bool
   ; type conversion functions
   "none_to_bool" none-to-bool
   "func_to_bool" func-to-bool
   "lnot_none"    lnot-none
   "lnot_func"    lnot-func))
