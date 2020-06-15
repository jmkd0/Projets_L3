#lang racket/base
(require racket/match
         racket/list
         "mips.rkt")
(provide optimise-mips)

(define (optimise-mips instrs)
  ; TODO several passes register by register?
  (for/fold ([instrs empty])
            ([instr instrs])
    (if (empty? instrs)
        (append instrs (list instr))
        (let ([instrs-but-last (drop-right instrs 1)]
              [prev-instr (last instrs)])
          (match (cons prev-instr instr)
            ; 2d sw is useless
            [(cons (lw reg mem) (sw reg mem))
             (displayln 0)
             instrs]
            ; drop 1st sw
            [(cons (sw first-reg mem) (sw sec-reg mem))
             #:when (not (equal? first-reg sec-reg))
             (append instrs (list instr))]
            ; drop 1st lw
            [(cons (lw reg first-mem) (lw reg sec-mem))
             #:when (not (equal? first-mem sec-mem))
             (append instrs-but-last (list instr))]
            ; replace 2d lw by move
            [(cons (sw first-reg mem) (lw sec-reg mem))
             #:when (not (equal? first-reg sec-reg))
             (append instrs (list (move sec-reg first-reg)))]
            ; anything else: nothing to do
            [_ (append instrs (list instr))])))))
