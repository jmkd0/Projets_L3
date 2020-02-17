#lang racket/base

(require "ast.rkt")

(provide (all-defined-out))

(define *baselib-types*
  (make-immutable-hash
   (list (cons '%add (Fun 'num (list 'num 'num))))))

(define *baselib*
  (make-immutable-hash
   (list (cons '%add
               (list (Lw 't0 (Mem 'sp 4))
                     (Lw 't1 (Mem 'sp 0))
                     (Add 'v0 't0 't1))))))

;; Ici %add est une fonction simple qui est systématiquement inlinée.
;;
;; En pratique pour la plupart des petites fonctions de la stdlib qui
;; correspondent à une instruction MIPS on pourra faire comme ça.
;;
;; Mais pour les fonctions plus complexes, par exemple celles définies
;; par l'utilisateurice, leur code sera à un label à l'endroit de leur
;; définition, et l'appelle de la fonction consistera en un
;; jump-and-link vers ce label.
