#lang racket/base

(require (prefix-in std- "types.rkt"))
(provide (all-defined-out))

(define lib
  (hash
   "input"      (std-func std-str (list std-str))
   ; print functions
   "print_int"  (std-func std-none (list std-int))
   "print_str"  (std-func std-none (list std-str))
   "print_bool" (std-func std-none (list std-bool))
   ; string functions
   "str_len"    (std-func std-int (list std-str))))

;; (name . return-type) of internal functions performing operations
(define ops
  (hash
   ; integer operations
   (list '+ std-int std-int)      (cons "add_ints" std-int)
   (list '- std-int std-int)      (cons "sub_ints" std-int)
   (list '* std-int std-int)      (cons "mul_ints" std-int)
   (list '/ std-int std-int)      (cons "div_ints" std-int)  ; TODO convert to float
   (list '== std-int std-int)     (cons "eq_ints" std-bool)
   (list '!= std-int std-int)     (cons "neq_ints" std-bool)
   (list '> std-int std-int)      (cons "gt_ints" std-bool)
   (list '< std-int std-int)      (cons "lt_ints" std-bool)
   (list '>= std-int std-int)     (cons "gte_ints" std-bool)
   (list '<= std-int std-int)     (cons "lte_ints" std-bool)
   (list 'lnot std-int)           (cons "lnot_bool" std-bool)
   ; bool operations
   (list '+ std-bool std-bool)    (cons "add_ints" std-int)
   (list '- std-bool std-bool)    (cons "sub_ints" std-int)
   (list '* std-bool std-bool)    (cons "mul_ints" std-int)
   (list '/ std-bool std-bool)    (cons "div_ints" std-int) ; TODO convert to float
   (list '== std-bool std-bool)   (cons "eq_ints" std-bool)
   (list '!= std-bool std-bool)   (cons "neq_ints" std-bool)
   (list '> std-bool std-bool)    (cons "gt_ints" std-bool)
   (list '< std-bool std-bool)    (cons "lt_ints" std-bool)
   (list '>= std-bool std-bool)   (cons "gte_ints" std-bool)
   (list '<= std-bool std-bool)   (cons "lte_ints" std-bool)
   (list 'land std-bool std-bool) (cons "land_bools" std-bool)
   (list 'lor std-bool std-bool)  (cons "lor_bools" std-bool)
   (list 'lnot std-bool)          (cons "lnot_bool" std-bool)
   ; string operations
   (list '== std-str std-str)     (cons "eq_strs" std-bool)
   (list '!= std-str std-str)     (cons "neq_strs" std-bool)
   (list '+ std-str std-str)      (cons "add_strs" std-str)
   (list 'lnot std-str)          (cons "lnot_str" std-bool)
  ; none operations
   (list 'lnot std-none)          (cons "lnot_none" std-bool)))
  ; TODO func operations. Cannot do "not func" although func can be in test condition
