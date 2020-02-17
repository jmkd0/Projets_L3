  .data
newline: .asciiz "\n"
str_1: .asciiz "coucou yope !"

  .text
  .globl main
_pair:
  li $a0, 8
  li $v0, 9
  syscall
  lw $t0, 4($sp)
  sw $t0, -4($v0)
  lw $t0, 0($sp)
  sw $t0, 0($v0)
  jr $ra
main:
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  la $v0, str_1
  addi $sp, $sp, -4
  sw $v0, 0($sp)
  lw $a0, 0($sp)
  li $v0, 4
  syscall
  addi $sp, $sp, 4
  la $a0, newline
  li $v0, 4
  syscall
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  jr $ra
