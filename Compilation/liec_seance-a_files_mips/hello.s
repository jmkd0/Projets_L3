.text
.globl main

main:
  li $v0, 4
  la $a0, hw
  syscall
  jr $ra

.data
hw: .asciiz "Hello, world!\n"
