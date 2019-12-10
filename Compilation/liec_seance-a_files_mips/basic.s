.text
.globl main

main:
  nop
  li $t0, 42
  li $t1, 9
  add $t2, $t0, $t1
  move $a0, $t2
  li $v0, 1
  syscall
  jr $ra
