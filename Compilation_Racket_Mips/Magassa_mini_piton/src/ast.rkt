#lang racket/base

(provide (all-defined-out))


;;; parsed syntax

;;; Définition d'une variable
;; type id "=" expr
(struct Pvardef (id expr type pos)          #:transparent)

;;; Rédefinition d'une variable
;; id "=" expr
(struct Pvar    (id expr pos)				#:transparent)

;;; Définition d'une fonction
;; ( "rec" )? type-ret id "(" args ":" type-args ")" body
(struct Pfundef (rec id args body type pos) #:transparent)

;;; Identifiant
;; id
(struct Pident  (id pos)                    #:transparent)

;;; Appel de fonction
;; id args
(struct Pcall   (id args pos)               #:transparent)

;;; Condition
;; "if" yes "else" no
(struct Pcond   (test yes no pos)           #:transparent)

;;; Boucle 
;; "while" test body
(struct Ploop   (test body pos)             #:transparent)

;;; Bloc de fonction
;; "{" expr ( ";" expr )* return sexpr "}" 
(struct Pfunblock (exprs ret pos)           #:transparent)

;;; Bloc
;; "{" expr ( ";" expr )* "}"
(struct Pblock  (exprs pos)                 #:transparent)

;;; Constante
;; value
(struct Pconst  (type value pos)            #:transparent)



;;; Arbre de syntaxe abstraite (AST)

;;; Re/Definition
;; Lier l'identifiant <n> à <v>.
(struct Let (n v)                      #:transparent)

;;; Function
;; Compiler la clôture et déclarer un label <id>.
(struct Func (id closure)              #:transparent)

;;; Variable
;; Référence à la variable <n>.
(struct Var (n)                        #:transparent)

;;; Condition
;; Compiler le <test>, le <yes> et le <no>.
(struct Cond (test yes no)             #:transparent)

;;; Boucle
;; Compiler le <body> et le <test>.
(struct Loop (test body)               #:transparent)

;;; Bloc
;; Compiler <body> tout en actualisant l'environnement.
(struct Block (body)                   #:transparent)

;;; Constante
;; Compiler la valeur <n>
(struct Const (n)                      #:transparent)

;;; Null
;; Revient à compiler (struct Const (0))
(struct Null ()                        #:transparent)

;;; Pair
;; Compiler <a> puis <b>
(struct Pair (a b)                     #:transparent)

;;; Data
;; Charger l'adresse de <l>
(struct Data (l)                       #:transparent)

;;; First
;; Récupérer le premier élément d'une pair <p>
(struct First (p)                      #:transparent)

;;; Second
;; Récupérer le deuxième élément d'une pair <p>
(struct Second (p)                     #:transparent)

;;; Opérations
;; Compiler une opérations (arithmétiques/comparaison) en 
;; compilant les valeurs <v1> et <v2> 
(struct Op (symbol v1 v2)              #:transparent)

;;; Bloc de fonction
;; Compiler le <body> et le <ret> de la fonction
(struct Funblock (body ret)            #:transparent)

;;; Call
;; Pour l'instant nous ne compilons rien, nous exécutons seulement
;; des Op et des Systcall
(struct Call    (id args)              #:transparent)

;;; Appel systèmes
;; Compiler <value> 
(struct Systcall (id value)            #:transparent)

;;; Clôture
(struct Closure (rec? args body env)   #:transparent)


;;; Types

;;; Entier (Integer)
(define Int 'int)

;;; Chaîne de caractères (Strings)
(define Str 'str)

;;; Booleen (Booleans)
(define Bool 'bool)

;;; Nil / the empty list
(define Nil 'nil)

;;; Anything
(define Any 'any)

;;; List of <t>
(struct Lst (t)                             #:transparent)

;;; Function that takes <args> and returns <ret>
(struct Fun (ret args)                      #:transparent)
