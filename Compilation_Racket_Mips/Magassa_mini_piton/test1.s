.data

.text
.globl main
main:
move $fp, $sp
	_main:
li $v0, 42
addi $sp, $sp, -4
sw $v0, 0($sp)
lw $v0, -4($fp)
addi $sp, $sp, -4
sw $v0, 0($sp)
li $v0, 42
lw $t0, 0($sp)
addi $sp, $sp, 4
move $t1, $v0
sne $t9, $t0, $t1
addi $sp, $sp, -4
sw $v0, 0($sp)
bnez $t9, then_1
beqz $t9, else_1
	then_1:
li $v0, 1
move $a0, $v0
li $v0, 1
syscall
b endif_1
	else_1:
li $v0, 0
move $a0, $v0
li $v0, 1
syscall
	endif_1:
li $v0, 0
jr $ra
move $t5, $v0
li $v0, 1
move $a0, $t5
syscall
li $v0, 0
jr $ra
