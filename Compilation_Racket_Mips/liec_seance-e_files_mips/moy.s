.data
label1: .asciiz "Entrer vos notes, en finissant par -1"
label2: .asciiz "Note numero "
espace: .asciiz ": "
label4: .asciiz "Votre moyenne est: "
ligne: .asciiz "\n"
n:      .word 0
moy:    .word 0
test_float:   .float -1.0
.text
.globl main

while:
    li $v0,4        # Affichage de "Note numero"
    la $a0, label2
    syscall

    addi $a1,$a1, 1
    move $a0, $a1      # Affichage du compteur
    li $v0, 1
    syscall

    li $v0,4        # Créer de l'espace 
    la $a0, espace
    syscall

    li $v0, 6       # Lecture de la note entrée
    syscall
    mov.s $f2, $f0

    jal if
    
   if:
      li $s1, -1
      cvt.w.s $f3, $f2
      mfc1 $s2, $f3
      beq $s2, $s1, end_while
      add.s $f1, $f1, $f2
      b while

end_while:
        li $v0, 4
        la $a0, label4
        syscall

        sub $a1, $a1, 1
        mtc1 $a1, $f3      # Convertion du compteur en float
        cvt.s.w $f3, $f3

        div.s $f1, $f1, $f3

        mov.s $f12, $f1  # Affichage de la moyenne
        li $v0, 2
        syscall

        li $v0,4        # Aller à la ligne
        la $a0, ligne
        syscall

        li $v0, 10        # Exit du programme
        syscall

main:
    li $v0,4
    la $a0, label1
    syscall

    li $v0,4        # Aller à la ligne
    la $a0, ligne
    syscall
    lw $a1, n           # On initialise n à 1
    jal while
  

   




