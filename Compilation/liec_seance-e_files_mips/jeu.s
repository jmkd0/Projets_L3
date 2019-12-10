prng_state:   .word	               42
.data
max:          .word                300
s1:           .asciiz              "Le nombre est entre 0 et "
s2:           .asciiz              "Entrez un nombre: \n"
s3:           .asciiz              "Le nombre est trop grand.\n"
s4:           .asciiz              "Le nombre est trop petit.\n"
s5:           .asciiz              "Félicitation.\n"
ligne:           .asciiz              "\n"
.text
.globl main

prng:
  move $t3, $a0                    # t3 = max
    
  lw $t0 prng_state
  li $t1 1664525
  mul $t0 $t0 $t1                 
  li $t1 1013904223
  addu $t0 $t0 $t1              
  div $t0, $t3                    
  mfhi $v0                         
    
  jr $ra                       

jeu: 
  move $s0, $a0                    # s0 = max	
  li $v0 4                         # affichage de Le nombre est entre 0 et
  la $a0 s1
  syscall  

  li $v0 1			               #Affichage du max
  move $a0 $s0
  syscall  

  li $v0 4                         #aller à nouvelle ligne
  la $a0 ligne
  syscall                          
  
  move $a0, $s0
  addi $sp, $sp, -4                # sauvegarde de ra
  sw $ra, 0($sp)                   
  jal prng                         # appel de prng
  lw $ra, 0($sp)                   # remettre ra à sa position initiale
  addi $sp, $sp, 4                 
  
  move $t0 $v0                     # $t0 = n                     
  li $t1 -1                        # $t1 = guess = -1
  
  while:                           # while guess != n
    beq $t0 $t1 end_while
    li $v0 4
    la $a0 s2                   
    syscall                        # print s2
    li $v0 5
    syscall                       
    move $t1 $v0                   
    bgt $t1 $t0 end_if           
    blt $t1 $t0 end_elif           
    b while
    
  end_if:
    li $v0 4
    la $a0 s3                   
    syscall                        # print s3
    b while
    
  end_elif:
    li $v0 4
    la $a0 s4                   
    syscall                        # print s4
    b while
    
  end_while:
    li $v0 4
    la $a0 s5                   
    syscall                        # print s5

  jr $ra                      

main:
  lw $a0, max
  addi $sp, $sp, -4                # sauvegarde de ra sur la pile
  sw $ra, 0($sp)
  jal jeu                          # appel du label jeu
  lw $ra, 0($sp)                   # restauration de ra
  addi $sp, $sp, 4
  
  li $v0, 10                       # exit
  syscall




