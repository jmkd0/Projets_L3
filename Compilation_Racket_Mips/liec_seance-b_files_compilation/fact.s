## fact.s
## Dans ce fichier on a compilé à la main le fichier fact.c
##
## Attention, le code assembleur présenté ici est mieux optimisé que ce que
## saurait faire un compilateur naïf.

.data
str_120: .asciiz "n? "
str_121: .asciiz "n! = "
str_122: .asciiz "\n"

.text
.globl main

fact:
  # reçoit n dans a0
  seq $t9, $a0, $0        # if (n == 0) t9 = 1; else t9 = 0
  bnez $t9, then_123      # si condition déjà valide sauter à then_123
  li $t0, 1
  seq $t9, $a0, $t0       # if (n == 1) t9 = 1; else t9 = 0
  beqz $t9, else_123      # si condition fausse sauter à else_123
then_123:
  li $v0, 1               # valeur de retour = 1
  b fact_ret              # retourner
else_123:                 # pas de else dans ce if donc c'est vide
endif_123:
  # calcul de "fact(n - 1)"
  addi $sp, $sp, -8       # on réserve deux places sur la pile
  sw $ra, 0($sp)          # on sauve ra
  sw $a0, 4($sp)          # on sauve n
  addi $a0, $a0, -1       # n = n - 1
  jal fact                # appel récursif
  lw $ra, 0($sp)          # on rétabli ra
  lw $a0, 4($sp)          # on rétabli n
  addi $sp, $sp, 8        # on rend les deux places sur la pile
  mul $v0, $a0, $v0       # valeur de retour = n * fact(n-1)
fact_ret:
  jr $ra                  # on a juste à faire le return, il n'y avait pas de
                          # registres sous la responsabilité de l'appelée à
                          # sauvegarder


factloop:
  li $t0, 1               # r = 1 (ici on utilise un registre pour r parce
                          # qu'on compile à la main, en pratique un compilateur
                          # sans optimisation ne saura pas faire d'allocation
                          # de registre intelligente et donc réservera
                          # probablement une place dans la pile, comme on le
                          # voit dans le main par exemple)
loop_124:
  sgt $t9, $a0, $0        # if (n > 0) t9 = 1; else t9 = 0
  beqz $t9, endloop_124   # si condition fausse, sauter à endloop_124
  mul $t0, $t0, $a0       # r = r * n
  addi $a0, $a0, -1       # n = n - 1
  b loop_124              # sauter inconditionnellement à loop_124
endloop_124:
  move $v0, $t0           # valeur de retour = r
factloop_ret:
  jr $ra                  # retourner



main:
  addi $sp, $sp, -8       # réservation de deux places sur la pile : une pour
                          # la variable locale "num" (qui n'est pas
	                        # initialisée), et une pour fp
  sw $fp 4($sp)           # sauvegarde de fp
  move $fp, $sp           # on retient du coup que notre variable locale "num"
                          # est à l'adresse 0($fp) (qui ne changera pas même si
                          # on change la valeur de $sp localement)

  li $v0, 4
  la $a0, str_120
  syscall                 # print_string(str_120)

  li $v0, 5
  syscall                 # v0 = read_int

  sw $v0, 0($fp)          # num = v0

  li $v0, 4,
  la $a0, str_121
  syscall                 # print_string(str_121)

  # maintenant on va appeler la fonction fact
  # il faut qu'on sauvegarde notre ra !
  addi $sp, $sp, -4       # réservation d'une place sur la pile pour sauver ra
  sw $ra, 0($sp)          # sauvegarde de ra

  # passage des arguments
  lw $a0, 0($fp)          # n = num (grâce à fp, pas grave si on a modifié sp)

  jal fact                # hop on appelle la fonction

  lw $ra, 0($sp)          # on rétablit tout de suite ra
  addi $sp, $sp, 4        # on rend la place sur la pile

  move $a0, $v0           # a0 = fact(num)
  li $v0, 1
  syscall                 # print_int(a0)

  li $v0, 4
  la $a0, str_122
  syscall                 # print_string(str_122)

  lw $fp, 4($sp)          # on rétablit fp
  addi $sp, $sp, 8        # on libère la place prise se la pile

  li $v0, 0               # valeur de retour = 0

  jr $ra                  # retourner
