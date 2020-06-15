.data

.text
.globl main
main:
move $fp, $sp
	_main:
li $v0, 42
move $a0, $v0
li $v0, 1
syscall
li $v0, 0
jr $ra
move $t5, $v0
li $v0, 1
move $a0, $t5
syscall
li $v0, 0
jr $ra
