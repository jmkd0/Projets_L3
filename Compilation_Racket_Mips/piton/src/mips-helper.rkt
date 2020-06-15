#lang racket/base

(require racket/match
         racket/list
         "mips.rkt")
(provide move-val
         push-next-activlnk
         apply-bininstr
         apply-uninstr)

;; Move value (number, register, mem, label, outer-mem)
;; to location (register, local mem, outer-mem)
(define (move-val dest-loc src-val)
  (if (or (not dest-loc) (equal? dest-loc src-val))
      empty
      (let-values ([(pre-instrs dest-loc src-val) (fetch-if-outer dest-loc src-val)])
        ; $t9 register used as temp register for memory operations
        (define move-instrs
          (match (cons dest-loc src-val)
            ; number to register
            [(cons (? reg?) (? number?)) (list (li dest-loc src-val))]
            ; register to register
            [(cons (? reg?) (? reg?)) (list (move dest-loc src-val))]
            ; mem to register
            [(cons (? reg?) (? mem?)) (list (lw dest-loc src-val))]
            ; label to register
            [(cons (? reg?) (? label?)) (list (la dest-loc src-val))] ; la for str, lw for num

            ; number to mem
            [(cons (? mem?) (? number?)) (list (li $t9 src-val)
                                               (sw $t9 dest-loc))]
            ; register to mem
            [(cons (? mem?) (? reg?)) (list (sw src-val dest-loc))]
            ; mem to mem
            [(cons (? mem?) (? mem?)) (list (lw $t9 src-val)
                                            (sw $t9 dest-loc))]
            ; label to mem
            [(cons (? mem?) (? label?)) (list (la $t9 src-val) ; la for str, lw for num
                                              (sw $t9 dest-loc))]))
        (append pre-instrs move-instrs))))

;; Handles outer scope values for <move-val>
;; return instrs, dest-loc, src-val
(define (fetch-if-outer dest-loc src-val)
  (let-values
       ([(dest-instrs dest-loc)
        (match dest-loc
          ; transform outer-mem into mem by fetching outer ssp
          [(outer-mem level-offset stack-offset)
           ; use dedicated temp register $t8
           (values (fetch-outer-sp level-offset $t8)
                   (mem stack-offset $t8))]
          [_ (values empty dest-loc)])]
        [(src-instrs src-val)
        (match src-val
          ; transform outer-mem into mem by fetching outer $sp
          [(outer-mem level-offset stack-offset)
           ; use dedicated temp register $t7
           (values (fetch-outer-sp level-offset $t7)
                   (mem stack-offset $t7))]
          [_ (values empty src-val)])])

    (values (append dest-instrs src-instrs)
            dest-loc
            src-val)))

;; Fetch stack pointer of the outer scope at <level-offset> and store it into <reg>
;; <return> instructions
;; http://pages.cs.wisc.edu/~fischer/cs536.s06/course.hold/html/NOTES/8.RUNTIME-VAR-ACCESS.html
(define (fetch-outer-sp level-offset reg)
  ; starting from $sp, walk up the activation link chain until we reach outer level
  (append (list (move reg $sp))
          (for/list ([i level-offset])
            (lw reg (mem 0 reg)))))

;; Move into <dest-loc> the value of activation link to push on stack before a call
;; http://pages.cs.wisc.edu/~fischer/cs536.s06/course.hold/html/NOTES/8.RUNTIME-VAR-ACCESS.html
;; <return> instructions
(define (push-next-activlnk caller-level callee-level dest-loc)
  (if (< caller-level callee-level)
      (move-val dest-loc (mem $sp 0)) ;; push to callee activation link of caller
      (let ([level-offset (- caller-level callee-level)])
        (append (list (la $t9 (mem 0 $sp)))
                (for/list ([i level-offset])
                  (lw $t9 (mem 0 $t9)))
                (move-val dest-loc $t9)))))

;; Apply unary operation instruction
;; return instrs
(define (apply-uninstr instr dest-loc src-val)
  ; load src into temp register if needed
  (define-values (load-src-instrs loaded-val)
    (load-lhs-val src-val $t6))
  ; use a temp destination register if needed
  (define tmp-dest-loc (get-tmp-dest-loc dest-loc $t5))
  ; save to destination from temp register if needed
  (define save-dest-instrs (save-dest-loc dest-loc tmp-dest-loc))

  (append load-src-instrs
          (list (instr tmp-dest-loc loaded-val))
          save-dest-instrs))

;; Apply binary operation instruction
;; return instrs
(define (apply-bininstr instr dest-loc lhs-val rhs-val)
  ; load lhs into temp register if needed
  (define-values (load-lhs-instrs loaded-lhs-val)
    (load-lhs-val lhs-val $t6))
  ; load rhs in temp register if needed and if different from lhs,
  ; else reuse result of <load-lhs-val>
  (define-values (load-rhs-instrs loaded-rhs-val)
    (if (equal? rhs-val lhs-val)
        (values empty loaded-lhs-val)
        (load-rhs-val rhs-val $t5)))
  ; use a temp destination register if needed
  (define tmp-dest-loc (get-tmp-dest-loc dest-loc $t4))
  ; save to destination from temp register if needed
  (define save-dest-instrs (save-dest-loc dest-loc tmp-dest-loc))

  (append load-lhs-instrs
          load-rhs-instrs
          (list (instr tmp-dest-loc loaded-lhs-val loaded-rhs-val))
          save-dest-instrs))

;; Load source value if remote (mem or outer-mem) so it can
;; be passed as first argument of a mips instruction (no literal allowed)
;; return instrs, val
(define (load-lhs-val src-val reg)
  (if (or (mem? src-val) (outer-mem? src-val) (number? src-val))
      (values (move-val reg src-val)
              reg)
      (values empty
              src-val)))

;; Load source value if remote (mem or outer-mem) so it can
;; be passed as second argument of a mips instruction (literals are allowed)
(define (load-rhs-val src-val reg)
  (if (or (mem? src-val) (outer-mem? src-val))
      (values (move-val reg src-val)
              reg)
      (values empty
              src-val)))

;; <return> temp register for destination if remote (mem or outer-mem)
;; return loc
(define (get-tmp-dest-loc dest-loc reg)
  (if (or (mem? dest-loc) (outer-mem? dest-loc))
      reg
      dest-loc))

;; Save temp register to destination if remote (mem or outer-mem)
;; return instrs
(define (save-dest-loc dest-loc reg)
  (if (or (mem? dest-loc) (outer-mem? dest-loc))
      (move-val dest-loc reg)
      empty))
