  .data
newline: .asciiz "\n"

  .text
  .globl main
main:
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  li $v0, 42
  addi $sp, $sp, -4
  sw $v0, 0($sp)
  li $v0, 9
  addi $sp, $sp, -4
  sw $v0, 0($sp)
  lw $t0, 4($sp)
  lw $t1, 0($sp)
  add $v0, $t0, $t1
  addi $sp, $sp, 8
  addi $sp, $sp, -4
  sw $v0, 0($sp)
  li $v0, 9
  addi $sp, $sp, -4
  sw $v0, 0($sp)
  lw $t0, 4($sp)
  lw $t1, 0($sp)
  add $v0, $t0, $t1
  addi $sp, $sp, 8
  addi $sp, $sp, -4
  sw $v0, 0($sp)
  li $v0, 9
  addi $sp, $sp, -4
  sw $v0, 0($sp)
  lw $t0, 4($sp)
  lw $t1, 0($sp)
  add $v0, $t0, $t1
  addi $sp, $sp, 8
  move $a0, $v0
  li $v0, 1
  syscall
  la $a0, newline
  li $v0, 4
  syscall
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  jr $ra
