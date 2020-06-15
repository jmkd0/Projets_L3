.data
str_g5868: .asciiz "True"
str_g5869: .asciiz "False"
str_g5883: .asciiz "IndexError: string index out of range"
str_g5887: .asciiz "ZeroDivisionError: division by zero"
.text
.globl main
# func str_len
func_g5860:
lw $a0 -4($sp)
li $v0 0
while_g5861:
lb $t0 0($a0)
beqz $t0 endwhile_g5861
addi $a0 $a0 1
addi $v0 $v0 1
b while_g5861
endwhile_g5861:
jr $ra
# func eq_strs
func_g5862:
lw $a0 -4($sp)
lw $a1 -8($sp)
while_g5863:
lb $t0 0($a0)
lb $t1 0($a1)
if_g5864:
beq $t0 $t1 endif_g5864
li $v0 0
jr $ra
endif_g5864:
beqz $t0 endwhile_g5863
beqz $t1 endwhile_g5863
addi $a0 $a0 1
addi $a1 $a1 1
b while_g5863
endwhile_g5863:
li $v0 1
jr $ra
# func str_to_bool
func_g5865:
lw $a0 -4($sp)
lb $a0 0($a0)
sne $v0 $a0 0
jr $ra
# func print_bool
func_g5866:
lw $a0 -4($sp)
li $v0 4
if_g5867:
beqz $a0 else_g5867
la $a0 str_g5868
b endif_g5867
else_g5867:
la $a0 str_g5869
endif_g5867:
syscall
li $a0 10
li $v0 11
syscall
jr $ra
# func lnot_str
func_g5870:
lw $a0 -4($sp)
lb $a0 0($a0)
seq $v0 $a0 0
jr $ra
# func neq_strs
func_g5871:
lw $a0 -4($sp)
lw $a1 -8($sp)
while_g5872:
lb $t0 0($a0)
lb $t1 0($a1)
if_g5873:
beq $t0 $t1 endif_g5873
li $v0 1
jr $ra
endif_g5873:
beqz $t0 endwhile_g5872
beqz $t1 endwhile_g5872
addi $a0 $a0 1
addi $a1 $a1 1
b while_g5872
endwhile_g5872:
li $v0 0
jr $ra
# func input
func_g5874:
lw $a0 -4($sp)
li $v0 4
syscall
li $a0 256
li $v0 9
syscall
move $a0 $v0
li $a1 256
li $v0 8
syscall
move $v0 $a0
while_g5875:
lb $t0 0($a0)
beq $t0 10 endwhile_g5875
addi $a0 $a0 1
b while_g5875
endwhile_g5875:
sb $zero 0($a0)
jr $ra
# func add_strs
func_g5876:
lw $a0 -4($sp)
li $v0 0
while_g5879:
lb $t0 0($a0)
beqz $t0 endwhile_g5879
addi $a0 $a0 1
addi $v0 $v0 1
b while_g5879
endwhile_g5879:
sw $v0 -12($sp)
lw $a0 -8($sp)
li $v0 0
while_g5880:
lb $t0 0($a0)
beqz $t0 endwhile_g5880
addi $a0 $a0 1
addi $v0 $v0 1
b while_g5880
endwhile_g5880:
lw $t0 -4($sp)
lw $t1 -8($sp)
lw $t2 -12($sp)
move $t3 $v0
add $a0 $t2 $t3
addi $a0 $a0 1
li $v0 9
syscall
move $t4 $v0
while_g5877:
lb $t5 0($t0)
beqz $t5 endwhile_g5877
sb $t5 0($t4)
addi $t0 $t0 1
addi $t4 $t4 1
b while_g5877
endwhile_g5877:
while_g5878:
lb $t5 0($t1)
beqz $t5 endwhile_g5878
sb $t5 0($t4)
addi $t1 $t1 1
addi $t4 $t4 1
b while_g5878
endwhile_g5878:
sb $zero 0($t4)
jr $ra
# func char_at_index
func_g5881:
lw $a0 -4($sp)
lw $a1 -8($sp)
li $t0 0
while_g5884:
lb $t1 0($a0)
beqz $t1 err_g5882
beq $t0 $a1 endwhile_g5884
addi $a0 $a0 1
addi $t0 $t0 1
b while_g5884
endwhile_g5884:
li $a0 2
li $v0 9
syscall
sb $t1 0($v0)
sb $zero 1($v0)
jr $ra
err_g5882:
la $a0 str_g5883
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $v0 10
syscall
# func div_ints
func_g5885:
lw $a0 -4($sp)
lw $a1 -8($sp)
beqz $a1 err_g5886
div $v0 $a0 $a1
jr $ra
err_g5886:
la $a0 str_g5887
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $v0 10
syscall
main:
li $t9 1
sw $t9 -4($sp)
move $a0 $t9
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
li $t9 2
sw $t9 -4($sp)
move $a0 $t9
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
lw $t9 -4($sp)
sw $t9 -8($sp)
move $a0 $t9
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
li $a0 3
li $a1 4
add $t4 $a0 $a1
sw $t4 -12($sp)
move $a0 $t4
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
li $a0 5
li $a1 6
add $t4 $a0 $a1
sw $t4 -16($sp)
move $a0 $t4
li $a1 7
mul $t4 $a0 $a1
sw $t4 -20($sp)
move $a0 $t4
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
if_g5888:
li $t9 1
beqz $t9 else_g5888
li $t9 8
sw $t9 -24($sp)
move $a0 $t9
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
b endif_g5888
else_g5888:
nop
endif_g5888:
if_g5889:
li $t9 0
beqz $t9 else_g5889
li $a0 9
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
b endif_g5889
else_g5889:
li $t9 10
sw $t9 -28($sp)
move $a0 $t9
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
endif_g5889:
if_g5890:
li $t9 1
beqz $t9 else_g5890
li $t9 11
sw $t9 -32($sp)
move $a0 $t9
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
b endif_g5890
else_g5890:
li $t9 12
sw $t9 -32($sp)
move $a0 $t9
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
endif_g5890:
if_g5891:
li $t9 0
beqz $t9 else_g5891
li $t9 13
sw $t9 -36($sp)
move $a0 $t9
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
b endif_g5891
else_g5891:
li $t9 14
sw $t9 -36($sp)
move $a0 $t9
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
endif_g5891:
li $t9 0
sw $t9 -40($sp)
while_g5892:
lw $a0 -40($sp)
li $a1 5
slt $t9 $a0 $a1
beqz $t9 endwhile_g5892
lw $t9 -40($sp)
sw $t9 -44($sp)
move $a0 $t9
li $v0 1
syscall
li $a0 10
li $v0 11
syscall
lw $a0 -40($sp)
li $a1 1
add $t4 $a0 $a1
sw $t4 -40($sp)
b while_g5892
endwhile_g5892:
jr $ra
