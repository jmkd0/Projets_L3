 
#lang racket/base

(require racket/match
         racket/list
         "mips.rkt"
         "ast.rkt")

(provide mips-emit)
(provide comp)

;;;;; Compilateur Python vers MIPS
;; la convention utilisée dans ce compilateur est
;; de toujours mettre la valeur calculée dans $v0 
;; et de placer dans $t9 la valeur des tests

(define accLoop 0) ;; accumulateur pour les boucles
(define accCond 0) ;; accumulateur pour les conditions
(define accStr  0) ;; accumulateur pour les chaînes de caractères
(define data (make-immutable-hash))
(provide comp)

;; Fonction réalisant les incrémentations pour nos accumulateurs récupérée 
;; sur https://stackoverflow.com
(define-syntax increment
  (syntax-rules ()
    ((_ x)   (begin (set! x (+ x 1)) x))
    ((_ x n) (begin (set! x (+ x n)) x))))

(define (comp expr env fp-sp) ;; le décalage entre sp et fp est fp - sp
  (match expr
    ((Null)
     ;; On représente Nil par l'adresse 0 (comme NULL en C)
     (define cnull (comp (Const 0) env fp-sp))
     (list 
      (list 
       (first cnull))
      (second env)))

    ((Const n)
     ;;; Vérifier la valeur obtenue dans notre n.
     (list
      (list 
       (cond
         ;;  Si il s'agit d'une chaîne, mettre dans .data et faire Lw. A faire !
         ;;  ((string? n)
         ;;  (increment accStr)
         ;;  (hash-set data (string-append "str_" (number->string accStr)) n)
         ;;  (La 'v0 (Lbl n))) ;; pas n mais le str_ qui contient n
         
         ;; Si il s'agit d'une valeur booléenne, mettre soit 0 (false), soit 1 (true) afin
         ;; de respecter la convention 
         ((boolean? n)
          (if (eq? n #t) 
           (Li 'v0 1)
           (Li 'v0 0)))
          ;; Autres: donc il s'agit "forcément" d'un entier
          (else 
           (Li 'v0 n))))
      env))

    ((Data d)
     ;; Pointeur dans .data mis dans v0
     (list
      (list (La 'v0 (Lbl d)))
      env))

    ((Pair a b)
     ;; Paire (a . b)
     (append
      ;; d'abord on compile a pour avoir sa valeur dans v0 :
      (comp a env fp-sp)
      ;; ensuite on l'empile :
      (list (Addi 'sp 'sp -4)
            (Sw 'v0 (Mem 0 'sp)))
      ;; ensuite on compile b pour l'avoir dans v0 en
      ;; se rappelant qu'on est décalé par rapport à fp :
      (comp b env (- fp-sp 4))
      ;; ensuite on compile la paire :
      (list (Lw 't0 (Mem 0 'sp)) ;; on dépile a
            (Addi 'sp 'sp 4)
            (Move 't1 'v0) ;; on récupère b
            (Li 'a0 8) ;; on alloue 8 octets = 2 mots mémoire
            (Li 'v0 9)
            (Syscall)
            ;; l'adresse de la paire est déjà dans v0
            (Sw 't0 (Mem 0 'v0)) ;; dans le premier on écrit a
            (Sw 't1 (Mem 4 'v0))))) ;; dans le second on écrit b

    ((First p)
     ;; Premier élément de la paire p
     (append
      ;; on compile p pour avoir l'adresse de la paire dans v0 :
      (comp p env fp-sp)
      ;; on récupère le premier dans v0 :
      (list (Lw 'v0 (Mem 0 'v0)))))

    ((Second p)
     ;; Second élément de la paire p
     (append
      ;; on compile p pour avoir l'adresse de la paire dans v0 :
      (comp p env fp-sp)
      ;; on récupère le second élément dans v0
      (list (Lw 'v0 (Mem 4 'v0)))))

    ;; Opération en prenant en paramètre l'opérande et deux valeurs.
    ;; Il s'agit d'instructions arithmétiques mais également de comparaisons
    ((Op symbol v1 v2)
     ;; compiler la première valeur et la deuxième valeur
     (define cv1 (comp v1 env fp-sp))
     (define cv2 (comp v2 env fp-sp))
     (list
      (append

       (first cv1)
       (list (Addi 'sp 'sp -4)
             (Sw 'v0 (Mem 0 'sp)))
         
       (first cv2)
       
       (list (Lw 't0 (Mem 0 'sp)) ;; on dépile v1
             (Addi 'sp 'sp 4)
             (Move 't1 'v0) ;; on récupère v2
             (match symbol ;; On execute l'operation selon l'opérande
              ('+  (Add 'v0 't0 't1))
              ('-  (Sub 'v0 't0 't1))
              ('*  (Mul 'v0 't0 't1))
              ('/  (Div 'v0 't0 't1))
              ('== (Seq 't9 't0 't1))
              ('!= (Sne 't9 't0 't1))
              ('>  (Sgt 't9 't0 't1))
              ('<  (Slt 't9 't0 't1))
              ('>= (Sge 't9 't0 't1))
              ('<= (Sle 't9 't0 't1)))))
      env))


    ;; Appels systèmes. Pour l'instant, seulement pour l'affichage
    ((Systcall id value)
     (define cval (comp value env fp-sp))
     (list
      (append
       (first cval)
       (match id
        ('print_num (list (Move 'a0 'v0) (Li 'v0 1) (Syscall)))
        ('print_str (list (La 'a0 Lbl value) (Li 'v0 4) (Syscall)))))
      env))

    ;; Appel de fonction qui peuvent être des fonctions déclarées par l'utilisateur (pas encore
    ;; implémenté) ou des fonctions natives (appel systèmes ou opérations)
    ((Call id args)
     ;; Expression compilée qui va soit être un appel système, soit une opération
     ;; (define cargs (comp args env fp-sp))
     (let ((ce
      ;; (if (eq? id Closure))
      (if (eq? id (or 'print_num 'print_str))
        (comp (Systcall id (car args)) env fp-sp)
        (comp (Op id (car args) (car (cdr args))) env fp-sp))))

      (list
       (append 
        (first ce))
      second ce)))

    ;; Boucle qui compile d'abord le test puis va sur le label endloop 
    ;; si le test vaut 0 sinon on continue sur le label loop avec des
    ;; branchements vers le même label
    ((Loop test body)
     (increment accLoop)
     ;; On compile le test puis le corps de la boucle
     (define ctest (comp test env fp-sp))
     (define cbody (comp body env (- fp-sp 4)))
     (list
      (append
       ;; Instructions MIPS pour le test
       (first ctest)
       (list (Addi 'sp 'sp -4)
             (Sw 'v0 (Mem 0 'sp)))
       (list (Label (string-append "loop_" (number->string accLoop)))
             (Beqz 't9 (string-append "endloop_" (number->string accLoop))))
       ;; Instructions MIPS pour le corps de la boucle
       (first cbody)
       (list (B (string-append "loop_" (number->string accLoop))))
       (list (Label (string-append "endloop_" (number->string accLoop)))))
      (second cbody)))

    ;; Condition qui compile d'abord le test puis va sur le label then ou else 
    ;; Et une fois fini continue les instructions sur le label endif
    ((Cond test yes no)
     (increment accCond)
     ;;; On compile le test, le bloc then et le bloc else
     (define ctest (comp test env fp-sp))
     (define cyes (comp yes env (- fp-sp 4)))
     (define cno (comp no env (- fp-sp 8)))

     (list
      (append
       ;; On ajoute les instructions MIPS du test
       (first ctest)
       (list (Addi 'sp 'sp -4)
             (Sw 'v0 (Mem 0 'sp)))
       (list (Bnez 't9 (string-append "then_" (number->string accCond))) ;; paramètre yes à utiliser
             (Beqz 't9 (string-append "else_" (number->string accCond))))

       (list (Label (string-append "then_" (number->string accCond))))
       ;; On ajoute les instructions MIPS du bloc then
       (first cyes)
       (list (B (string-append "endif_" (number->string accCond))))

       (list (Label (string-append "else_" (number->string accCond))))
       ;; On ajoute les instructions MIPS du bloc else
       (first cno)

       ;; On continue sur le label endif la suite du programme
       (list (Label (string-append "endif_" (number->string accCond)))))
      env))


    ;;; Déclaration d'une fonction composé de id (nom de la fonction) et 
    ;;; de sa clôture
    ((Func id closure)
     (define cclosure (comp closure (hash-set env id (Mem fp-sp 'fp)) fp-sp))
     (list
      (append
       (if (eq? id 'main)
        (list (Label '_main)) ;; Main déjà existant
        (list (Label id)))
       (first cclosure))
      (second cclosure)))

    ;; Clôture... A faire !
    ((Closure rec? args body _)
     ;; Expression compilée avec 2 éléments: 1- instructions MIPS, 2- environnement
     (define cbody (comp body env fp-sp))
     (list
      (append
       (first cbody))
      (second cbody)))

    ;; Bloc de fonction qui agit comme un bloc classique mais qui retourne également 
    ;; une valeur dans v0
    ((Funblock body ret)
     ;; On compile chaque expression en mettant dans une liste composée
     ;; de deux éléments : 1- l'expression MIPS, 2- l'environnement

     ;; On compile dans un premier temps le corps de la fonction
     (define cbody (foldl (lambda (expr acc)
              (let ((ce (comp expr (second acc) fp-sp)))
                (list (append (first acc)
                              (first ce))
                       (second ce))))
            (list '() env)
            body))

     ;; On compile la valeur de retour de la fonction et on 
     ;; la place dans v0
     (define cret (comp ret env fp-sp))

     ;; On ajoute les deux expressions compilées en ajoutant l'environnement
     ;; au corps de la fonction 
     (list
      (append
        (first cbody)
        (first cret)
        (list (Jr 'ra)))
      (second cbody)))


    ;; Bloc d'instructions utilisé pour le corps des conditions, 
    ;; des boucles, ou des fonctions.
    ((Block body)
     ;; On compile chaque expression en mettant dans une liste composée
     ;; de deux éléments : 1- l'expression MIPS, 2- l'environnement
     (foldl (lambda (expr acc)
              (let ((ce (comp expr (second acc) fp-sp)))
                (list (append (first acc)
                              (first ce))
                       (second ce))))
            (list '() env)
            body))


    ;; Re/Déclaration d'une variable
    ((Let n v)
     ;; On compile la valeur v en mettant dans une liste composée
     ;; de deux éléments : 1- l'expression MIPS, 2- l'environnement
     (define cv (comp v (hash-set env n (Mem (- fp-sp 4) 'fp)) (- fp-sp 4)))

     (list
      (append
       ;; on récupère seulement l'instruction MIPS
       (first cv)
       ;; on empile la variable locale :
       (list (Addi 'sp 'sp -4)
             (Sw 'v0 (Mem 0 'sp))))
      (second cv)))

    ;; Référence à une variable
    ((Var n)
     ;; on met la valeur de la variable dans v0 :
     (list
      (list (Lw 'v0 (hash-ref env n)))
      env))))



(define (mips-loc loc)
  (match loc
    ((Lbl l)   (format "~a" l))
    ((Mem b r) (format "~a($~a)" b r))))

(define (mips-emit instr)
  (match instr
    ((Move rd rs)     (printf "move $~a, $~a\n" rd rs))
    ((Li r i)         (printf "li $~a, ~a\n" r i))
    ((La r a)         (printf "la $~a, ~a\n" r (mips-loc a)))
    ((Addi rd rs i)   (printf "addi $~a, $~a, ~a\n" rd rs i))
    ((Add rd rs1 rs2) (printf "add $~a, $~a, $~a\n" rd rs1 rs2))
    ((Sub rd rs1 rs2) (printf "sub $~a, $~a, $~a\n" rd rs1 rs2))
    ((Mul rd rs1 rs2) (printf "mul $~a, $~a, $~a\n" rd rs1 rs2))
    ((Div rd rs1 rs2) (printf "div $~a, $~a, $~a\n" rd rs1 rs2))
    ((Lo rd)          (printf "mflo $~a\n" rd))
    ((Seq rd rs1 rs2) (printf "seq $~a, $~a, $~a\n" rd rs1 rs2))
    ((Sne rd rs1 rs2) (printf "sne $~a, $~a, $~a\n" rd rs1 rs2))
    ((Sgt rd rs1 rs2) (printf "sgt $~a, $~a, $~a\n" rd rs1 rs2))
    ((Slt rd rs1 rs2) (printf "slt $~a, $~a, $~a\n" rd rs1 rs2))
    ((Sle rd rs1 rs2) (printf "sle $~a, $~a, $~a\n" rd rs1 rs2))
    ((Sge rd rs1 rs2) (printf "sge $~a, $~a, $~a\n" rd rs1 rs2))
    ((And rd rs1 rs2) (printf "and $~a, $~a, $~a\n" rd rs1 rs2))
    ((Or rd rs1 rs2)  (printf "or $~a, $~a, $~a\n" rd rs1 rs2))
    ((B l)            (printf "b ~a\n" l))
    ((Bnez rs l)      (printf "bnez $~a, ~a\n" rs l))
    ((Beqz rs l)      (printf "beqz $~a, ~a\n" rs l))
    ((Sw r loc)       (printf "sw $~a, ~a\n" r (mips-loc loc)))
    ((Lw r loc)       (printf "lw $~a, ~a\n" r (mips-loc loc)))
    ((Syscall)        (printf "syscall\n"))
    ((Jr r)           (printf "jr $~a\n" r))
    ((Label l)        (printf "\t~a:\n" l))))

(define (mips-data data)
  (printf ".data\n")
  (hash-for-each data
                 (lambda (k v)
                   (printf "~a: .asciiz ~s\n" k v)))
  (printf "\n.text\n.globl main\nmain:\n")) ;; Peut-être à enlever

(mips-data data)
