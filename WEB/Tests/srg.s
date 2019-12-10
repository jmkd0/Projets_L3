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
  move $s0, $a0   
                   # s0 = max	
  li $v0 4                         # affichage de Le nombre est entre 0 et
  la $a0 s1
  syscall   

  li $v0 1			