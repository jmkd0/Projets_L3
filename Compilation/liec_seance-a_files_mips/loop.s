.text
.globl main

add_user_num:
  li $v0, 4
  la $a0, num1q
  syscall
  
  li $v0, 5
  syscall
  move $t0, $v0
  
  li $v0, 4
  la $a0, num2q
  syscall

  li $v0, 5
  syscall
  move $t1, $v0

  li $v0, 4
  la $a0, sum
  syscall

  add $a0, $t0, $t1
  li $v0, 1
  syscall

  li $v0, 4
  la $a0, nl
  syscall

  jr $ra
  
main:
  li $t2, 3
loop:
  beq $t2, $0, end_loop
  addi $t2, $t2, -1
  jal add_user_num
  b loop
end_loop:
  li $v0, 10
  syscall

.data
num1q: .asciiz "Please enter a first number: "
num2q: .asciiz "Please enter a second number: "
sum:   .asciiz "The sum of these numbers is: "
nl:    .asciiz "\n"
