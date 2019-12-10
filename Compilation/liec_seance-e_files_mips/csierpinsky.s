.data
espaces:    .asciiz "\t\t\t\n"
affiche:    .asciiz "#"
vide:   .asciiz " "
.text
.globl main

main:
  li $t0 1                         
  li $t1 2147483648                # on calcule la puissance 2^32

while1:
  bleu $t1, $t0, end_while1        # while x < 2**31
  move $t2, $t0                    # n = x
  
while2:
  beqz $t2, end_while2             
  andi $t3, $t2, 1                
  beqz $t3  else_while2           
  li $v0 4                        
  la $a0, affiche                    # affichage des dieses
  syscall
  b end_if_while2
  
else_while2:
  li $v0 4                         
  la $a0, vide                    
  syscall
  
end_if_while2:
  srl $t2, $t2, 1                  # n >>= 1
  b while2
  
end_while2:
  sll $t3, $t0, 1                  
  xor $t0, $t0, $t3                
  li $v0, 4                        
  la $a0, espaces                  
  syscall
  b while1
  
end_while1:
  jr $ra
  li $v0, 10                       # exit
  syscall
  

 
