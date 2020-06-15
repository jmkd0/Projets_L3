.data
str_g5905: .asciiz "True"
str_g5906: .asciiz "False"
str_g5920: .asciiz "IndexError: string index out of range"
str_g5924: .asciiz "ZeroDivisionError: division by zero"
str_g5935: .asciiz " "
str_g5937: .asciiz "a"
str_g5939: .asciiz "e"
str_g5941: .asciiz "i"
str_g5943: .asciiz "i"
str_g5945: .asciiz "u"
str_g5947: .asciiz "y"
str_g5949: .asciiz "0"
str_g5951: .asciiz "1"
str_g5953: .asciiz "2"
str_g5955: .asciiz "3"
str_g5957: .asciiz "4"
str_g5959: .asciiz "5"
str_g5961: .asciiz "6"
str_g5963: .asciiz "7"
str_g5965: .asciiz "8"
str_g5967: .asciiz "9"
str_g5969: .asciiz "0"
str_g5971: .asciiz "1"
str_g5973: .asciiz "2"
str_g5975: .asciiz "3"
str_g5977: .asciiz "4"
str_g5979: .asciiz "5"
str_g5981: .asciiz "6"
str_g5983: .asciiz "7"
str_g5985: .asciiz "8"
str_g5987: .asciiz "9"
str_g5990: .asciiz ""
str_g5994: .asciiz ""
str_g6000: .asciiz "ius"
str_g6001: .asciiz "s"
str_g6003: .asciiz "children"
str_g6004: .asciiz "child"
str_g6006: .asciiz "atoes"
str_g6007: .asciiz "ato"
str_g6009: .asciiz "ives"
str_g6010: .asciiz "ife"
str_g6012: .asciiz "men"
str_g6013: .asciiz "man"
str_g6015: .asciiz "ies"
str_g6016: .asciiz "y"
str_g6018: .asciiz "i"
str_g6019: .asciiz "ius"
str_g6021: .asciiz "ches"
str_g6022: .asciiz "ch"
str_g6024: .asciiz "shes"
str_g6025: .asciiz "sh"
str_g6027: .asciiz "xes"
str_g6028: .asciiz "x"
str_g6030: .asciiz ""
str_g6033: .asciiz " "
str_g6034: .asciiz " is "
str_g6035: .asciiz " "
str_g6036: .asciiz " is "
str_g6037: .asciiz " "
str_g6038: .asciiz ""
str_g6039: .asciiz "what do you want your poetry to be about? > "
str_g6042: .asciiz "please enter a subject > "
str_g6043: .asciiz "please enter a simpler subject > "
str_g6044: .asciiz "one a scale of 1 to 9, how poetic do you want to be? > "
str_g6046: .asciiz "0"
str_g6047: .asciiz "please enter a digit between 1 and 9 > "
str_g6049: .asciiz "an"
str_g6050: .asciiz "a"
.text
.globl main
# func str_len
func_g5897:
lw $a0 -4($sp)
li $v0 0
while_g5898:
lb $t0 0($a0)
beqz $t0 endwhile_g5898
addi $a0 $a0 1
addi $v0 $v0 1
b while_g5898
endwhile_g5898:
jr $ra
# func eq_strs
func_g5899:
lw $a0 -4($sp)
lw $a1 -8($sp)
while_g5900:
lb $t0 0($a0)
lb $t1 0($a1)
if_g5901:
beq $t0 $t1 endif_g5901
li $v0 0
jr $ra
endif_g5901:
beqz $t0 endwhile_g5900
beqz $t1 endwhile_g5900
addi $a0 $a0 1
addi $a1 $a1 1
b while_g5900
endwhile_g5900:
li $v0 1
jr $ra
# func str_to_bool
func_g5902:
lw $a0 -4($sp)
lb $a0 0($a0)
sne $v0 $a0 0
jr $ra
# func print_bool
func_g5903:
lw $a0 -4($sp)
li $v0 4
if_g5904:
beqz $a0 else_g5904
la $a0 str_g5905
b endif_g5904
else_g5904:
la $a0 str_g5906
endif_g5904:
syscall
li $a0 10
li $v0 11
syscall
jr $ra
# func lnot_str
func_g5907:
lw $a0 -4($sp)
lb $a0 0($a0)
seq $v0 $a0 0
jr $ra
# func neq_strs
func_g5908:
lw $a0 -4($sp)
lw $a1 -8($sp)
while_g5909:
lb $t0 0($a0)
lb $t1 0($a1)
if_g5910:
beq $t0 $t1 endif_g5910
li $v0 1
jr $ra
endif_g5910:
beqz $t0 endwhile_g5909
beqz $t1 endwhile_g5909
addi $a0 $a0 1
addi $a1 $a1 1
b while_g5909
endwhile_g5909:
li $v0 0
jr $ra
# func input
func_g5911:
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
while_g5912:
lb $t0 0($a0)
beq $t0 10 endwhile_g5912
addi $a0 $a0 1
b while_g5912
endwhile_g5912:
sb $zero 0($a0)
jr $ra
# func add_strs
func_g5913:
lw $a0 -4($sp)
li $v0 0
while_g5916:
lb $t0 0($a0)
beqz $t0 endwhile_g5916
addi $a0 $a0 1
addi $v0 $v0 1
b while_g5916
endwhile_g5916:
sw $v0 -12($sp)
lw $a0 -8($sp)
li $v0 0
while_g5917:
lb $t0 0($a0)
beqz $t0 endwhile_g5917
addi $a0 $a0 1
addi $v0 $v0 1
b while_g5917
endwhile_g5917:
lw $t0 -4($sp)
lw $t1 -8($sp)
lw $t2 -12($sp)
move $t3 $v0
add $a0 $t2 $t3
addi $a0 $a0 1
li $v0 9
syscall
move $t4 $v0
while_g5914:
lb $t5 0($t0)
beqz $t5 endwhile_g5914
sb $t5 0($t4)
addi $t0 $t0 1
addi $t4 $t4 1
b while_g5914
endwhile_g5914:
while_g5915:
lb $t5 0($t1)
beqz $t5 endwhile_g5915
sb $t5 0($t4)
addi $t1 $t1 1
addi $t4 $t4 1
b while_g5915
endwhile_g5915:
sb $zero 0($t4)
jr $ra
# func char_at_index
func_g5918:
lw $a0 -4($sp)
lw $a1 -8($sp)
li $t0 0
while_g5921:
lb $t1 0($a0)
beqz $t1 err_g5919
beq $t0 $a1 endwhile_g5921
addi $a0 $a0 1
addi $t0 $t0 1
b while_g5921
endwhile_g5921:
li $a0 2
li $v0 9
syscall
sb $t1 0($v0)
sb $zero 1($v0)
jr $ra
err_g5919:
la $a0 str_g5920
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $v0 10
syscall
# func div_ints
func_g5922:
lw $a0 -4($sp)
lw $a1 -8($sp)
beqz $a1 err_g5923
div $v0 $a0 $a1
jr $ra
err_g5923:
la $a0 str_g5924
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
li $v0 10
syscall
# func has_space
func_g5925:
lw $t9 -4($sp)
sw $t9 -32($sp)
sw $ra -24($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -28($sp)
addi $sp $sp -28
jal func_g5897
addi $sp $sp 28
lw $ra -24($sp)
sw $v0 -8($sp)
li $t9 0
sw $t9 -12($sp)
while_g5933:
lw $a0 -12($sp)
lw $a1 -8($sp)
slt $t9 $a0 $a1
beqz $t9 endwhile_g5933
if_g5934:
lw $t9 -4($sp)
sw $t9 -32($sp)
lw $t9 -12($sp)
sw $t9 -36($sp)
sw $ra -24($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -28($sp)
addi $sp $sp -28
jal func_g5918
addi $sp $sp 28
lw $ra -24($sp)
sw $v0 -16($sp)
move $t9 $v0
sw $t9 -32($sp)
la $t9 str_g5935
sw $t9 -36($sp)
sw $ra -24($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -28($sp)
addi $sp $sp -28
jal func_g5899
addi $sp $sp 28
lw $ra -24($sp)
move $t9 $v0
beqz $t9 else_g5934
li $v0 1
jr $ra
b endif_g5934
else_g5934:
nop
endif_g5934:
lw $a0 -12($sp)
li $a1 1
add $t4 $a0 $a1
sw $t4 -12($sp)
b while_g5933
endwhile_g5933:
li $v0 0
jr $ra
jr $ra
# func is_vowel
func_g5926:
if_g5936:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5937
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5936
li $v0 1
jr $ra
b endif_g5936
else_g5936:
nop
endif_g5936:
if_g5938:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5939
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5938
li $v0 1
jr $ra
b endif_g5938
else_g5938:
nop
endif_g5938:
if_g5940:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5941
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5940
li $v0 1
jr $ra
b endif_g5940
else_g5940:
nop
endif_g5940:
if_g5942:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5943
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5942
li $v0 1
jr $ra
b endif_g5942
else_g5942:
nop
endif_g5942:
if_g5944:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5945
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5944
li $v0 1
jr $ra
b endif_g5944
else_g5944:
nop
endif_g5944:
if_g5946:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5947
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5946
li $v0 1
jr $ra
b endif_g5946
else_g5946:
nop
endif_g5946:
li $v0 0
jr $ra
jr $ra
# func is_single_digit
func_g5927:
if_g5948:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5949
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5948
li $v0 1
jr $ra
b endif_g5948
else_g5948:
nop
endif_g5948:
if_g5950:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5951
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5950
li $v0 1
jr $ra
b endif_g5950
else_g5950:
nop
endif_g5950:
if_g5952:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5953
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5952
li $v0 1
jr $ra
b endif_g5952
else_g5952:
nop
endif_g5952:
if_g5954:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5955
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5954
li $v0 1
jr $ra
b endif_g5954
else_g5954:
nop
endif_g5954:
if_g5956:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5957
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5956
li $v0 1
jr $ra
b endif_g5956
else_g5956:
nop
endif_g5956:
if_g5958:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5959
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5958
li $v0 1
jr $ra
b endif_g5958
else_g5958:
nop
endif_g5958:
if_g5960:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5961
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5960
li $v0 1
jr $ra
b endif_g5960
else_g5960:
nop
endif_g5960:
if_g5962:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5963
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5962
li $v0 1
jr $ra
b endif_g5962
else_g5962:
nop
endif_g5962:
if_g5964:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5965
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5964
li $v0 1
jr $ra
b endif_g5964
else_g5964:
nop
endif_g5964:
if_g5966:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5967
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5966
li $v0 1
jr $ra
b endif_g5966
else_g5966:
nop
endif_g5966:
li $v0 0
jr $ra
jr $ra
# func letter_to_digit
func_g5928:
if_g5968:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5969
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5968
li $v0 0
jr $ra
b endif_g5968
else_g5968:
nop
endif_g5968:
if_g5970:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5971
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5970
li $v0 1
jr $ra
b endif_g5970
else_g5970:
nop
endif_g5970:
if_g5972:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5973
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5972
li $v0 2
jr $ra
b endif_g5972
else_g5972:
nop
endif_g5972:
if_g5974:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5975
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5974
li $v0 3
jr $ra
b endif_g5974
else_g5974:
nop
endif_g5974:
if_g5976:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5977
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5976
li $v0 4
jr $ra
b endif_g5976
else_g5976:
nop
endif_g5976:
if_g5978:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5979
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5978
li $v0 5
jr $ra
b endif_g5978
else_g5978:
nop
endif_g5978:
if_g5980:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5981
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5980
li $v0 6
jr $ra
b endif_g5980
else_g5980:
nop
endif_g5980:
if_g5982:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5983
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5982
li $v0 7
jr $ra
b endif_g5982
else_g5982:
nop
endif_g5982:
if_g5984:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5985
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5984
li $v0 8
jr $ra
b endif_g5984
else_g5984:
nop
endif_g5984:
if_g5986:
lw $t9 -4($sp)
sw $t9 -20($sp)
la $t9 str_g5987
sw $t9 -24($sp)
sw $ra -12($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -16($sp)
addi $sp $sp -16
jal func_g5899
addi $sp $sp 16
lw $ra -12($sp)
move $t9 $v0
beqz $t9 else_g5986
li $v0 9
jr $ra
b endif_g5986
else_g5986:
nop
endif_g5986:
jr $ra
# func get_prefix
func_g5929:
lw $t9 -4($sp)
sw $t9 -40($sp)
sw $ra -32($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -36($sp)
addi $sp $sp -36
jal func_g5897
addi $sp $sp 36
lw $ra -32($sp)
sw $v0 -12($sp)
if_g5988:
lw $a0 -8($sp)
li $a1 0
slt $t9 $a0 $a1
beqz $t9 else_g5988
li $t9 0
sw $t9 -8($sp)
b endif_g5988
else_g5988:
nop
endif_g5988:
if_g5989:
lw $a0 -8($sp)
lw $a1 -12($sp)
sgt $t9 $a0 $a1
beqz $t9 else_g5989
lw $t9 -12($sp)
sw $t9 -8($sp)
b endif_g5989
else_g5989:
nop
endif_g5989:
li $t9 0
sw $t9 -16($sp)
la $t9 str_g5990
sw $t9 -20($sp)
while_g5991:
lw $a0 -16($sp)
lw $a1 -8($sp)
slt $t9 $a0 $a1
beqz $t9 endwhile_g5991
lw $t9 -4($sp)
sw $t9 -40($sp)
lw $t9 -16($sp)
sw $t9 -44($sp)
sw $ra -32($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -36($sp)
addi $sp $sp -36
jal func_g5918
addi $sp $sp 36
lw $ra -32($sp)
sw $v0 -24($sp)
lw $t9 -20($sp)
sw $t9 -40($sp)
lw $t9 -24($sp)
sw $t9 -44($sp)
sw $ra -32($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -36($sp)
addi $sp $sp -36
jal func_g5913
addi $sp $sp 36
lw $ra -32($sp)
sw $v0 -20($sp)
lw $a0 -16($sp)
li $a1 1
add $t4 $a0 $a1
sw $t4 -16($sp)
b while_g5991
endwhile_g5991:
lw $v0 -20($sp)
jr $ra
jr $ra
# func get_suffix
func_g5930:
lw $t9 -4($sp)
sw $t9 -48($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5897
addi $sp $sp 44
lw $ra -40($sp)
sw $v0 -12($sp)
if_g5992:
lw $a0 -8($sp)
li $a1 0
slt $t9 $a0 $a1
beqz $t9 else_g5992
li $t9 0
sw $t9 -8($sp)
b endif_g5992
else_g5992:
nop
endif_g5992:
if_g5993:
lw $a0 -8($sp)
lw $a1 -12($sp)
sgt $t9 $a0 $a1
beqz $t9 else_g5993
lw $t9 -12($sp)
sw $t9 -8($sp)
b endif_g5993
else_g5993:
nop
endif_g5993:
la $t9 str_g5994
sw $t9 -16($sp)
li $t9 0
sw $t9 -20($sp)
while_g5995:
lw $a0 -20($sp)
lw $a1 -8($sp)
slt $t9 $a0 $a1
beqz $t9 endwhile_g5995
lw $a0 -12($sp)
lw $a1 -8($sp)
sub $t4 $a0 $a1
sw $t4 -24($sp)
move $a0 $t4
lw $a1 -20($sp)
add $t4 $a0 $a1
sw $t4 -28($sp)
lw $t9 -4($sp)
sw $t9 -48($sp)
lw $t9 -28($sp)
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5918
addi $sp $sp 44
lw $ra -40($sp)
sw $v0 -32($sp)
lw $t9 -16($sp)
sw $t9 -48($sp)
lw $t9 -32($sp)
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5913
addi $sp $sp 44
lw $ra -40($sp)
sw $v0 -16($sp)
lw $a0 -20($sp)
li $a1 1
add $t4 $a0 $a1
sw $t4 -20($sp)
b while_g5995
endwhile_g5995:
lw $v0 -16($sp)
jr $ra
jr $ra
# func replace_suffix
func_g5931:
lw $t9 -4($sp)
sw $t9 -40($sp)
sw $ra -32($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -36($sp)
addi $sp $sp -36
jal func_g5897
addi $sp $sp 36
lw $ra -32($sp)
sw $v0 -16($sp)
move $a0 $v0
lw $a1 -8($sp)
sub $t4 $a0 $a1
sw $t4 -20($sp)
lw $t9 -4($sp)
sw $t9 -40($sp)
lw $t9 -20($sp)
sw $t9 -44($sp)
sw $ra -32($sp)
la $t9 0($sp)
lw $t9 0($t9)
sw $t9 -36($sp)
addi $sp $sp -36
jal func_g5929
addi $sp $sp 36
lw $ra -32($sp)
sw $v0 -24($sp)
move $t9 $v0
sw $t9 -40($sp)
lw $t9 -12($sp)
sw $t9 -44($sp)
sw $ra -32($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -36($sp)
addi $sp $sp -36
jal func_g5913
addi $sp $sp 36
lw $ra -32($sp)
jr $ra
jr $ra
# func seems_singular
func_g5996:
lw $t9 -4($sp)
sw $t9 -24($sp)
li $t9 3
sw $t9 -28($sp)
sw $ra -16($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -20($sp)
addi $sp $sp -20
jal func_g5930
addi $sp $sp 20
lw $ra -16($sp)
sw $v0 -8($sp)
if_g5999:
lw $t9 -8($sp)
sw $t9 -24($sp)
la $t9 str_g6000
sw $t9 -28($sp)
sw $ra -16($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -20($sp)
addi $sp $sp -20
jal func_g5899
addi $sp $sp 20
lw $ra -16($sp)
move $t9 $v0
beqz $t9 else_g5999
li $v0 1
jr $ra
b endif_g5999
else_g5999:
nop
endif_g5999:
lw $t9 -4($sp)
sw $t9 -24($sp)
li $t9 1
sw $t9 -28($sp)
sw $ra -16($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -20($sp)
addi $sp $sp -20
jal func_g5930
addi $sp $sp 20
lw $ra -16($sp)
sw $v0 -8($sp)
move $t9 $v0
sw $t9 -24($sp)
la $t9 str_g6001
sw $t9 -28($sp)
sw $ra -16($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -20($sp)
addi $sp $sp -20
jal func_g5908
addi $sp $sp 20
lw $ra -16($sp)
jr $ra
jr $ra
# func singularize
func_g5997:
if_g6002:
lw $t9 -4($sp)
sw $t9 -48($sp)
la $t9 str_g6003
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5899
addi $sp $sp 44
lw $ra -40($sp)
move $t9 $v0
beqz $t9 else_g6002
la $v0 str_g6004
jr $ra
b endif_g6002
else_g6002:
nop
endif_g6002:
lw $t9 -4($sp)
sw $t9 -48($sp)
li $t9 5
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5930
addi $sp $sp 44
lw $ra -40($sp)
sw $v0 -8($sp)
if_g6005:
lw $t9 -8($sp)
sw $t9 -48($sp)
la $t9 str_g6006
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5899
addi $sp $sp 44
lw $ra -40($sp)
move $t9 $v0
beqz $t9 else_g6005
lw $t9 -4($sp)
sw $t9 -48($sp)
li $t9 5
sw $t9 -52($sp)
la $t9 str_g6007
sw $t9 -56($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5931
addi $sp $sp 44
lw $ra -40($sp)
jr $ra
b endif_g6005
else_g6005:
nop
endif_g6005:
lw $t9 -4($sp)
sw $t9 -48($sp)
li $t9 4
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5930
addi $sp $sp 44
lw $ra -40($sp)
sw $v0 -8($sp)
if_g6008:
lw $t9 -8($sp)
sw $t9 -48($sp)
la $t9 str_g6009
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5899
addi $sp $sp 44
lw $ra -40($sp)
move $t9 $v0
beqz $t9 else_g6008
lw $t9 -4($sp)
sw $t9 -48($sp)
li $t9 4
sw $t9 -52($sp)
la $t9 str_g6010
sw $t9 -56($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5931
addi $sp $sp 44
lw $ra -40($sp)
jr $ra
b endif_g6008
else_g6008:
nop
endif_g6008:
lw $t9 -4($sp)
sw $t9 -48($sp)
li $t9 3
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5930
addi $sp $sp 44
lw $ra -40($sp)
sw $v0 -8($sp)
if_g6011:
lw $t9 -8($sp)
sw $t9 -48($sp)
la $t9 str_g6012
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5899
addi $sp $sp 44
lw $ra -40($sp)
move $t9 $v0
beqz $t9 else_g6011
lw $t9 -4($sp)
sw $t9 -48($sp)
li $t9 3
sw $t9 -52($sp)
la $t9 str_g6013
sw $t9 -56($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5931
addi $sp $sp 44
lw $ra -40($sp)
jr $ra
b endif_g6011
else_g6011:
nop
endif_g6011:
lw $t9 -4($sp)
sw $t9 -48($sp)
li $t9 4
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5930
addi $sp $sp 44
lw $ra -40($sp)
sw $v0 -8($sp)
if_g6014:
lw $t9 -8($sp)
sw $t9 -48($sp)
li $t9 0
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5918
addi $sp $sp 44
lw $ra -40($sp)
sw $v0 -12($sp)
move $t9 $v0
sw $t9 -48($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5926
addi $sp $sp 44
lw $ra -40($sp)
sw $v0 -16($sp)
move $a0 $v0
seq $t4 $a0 0
sw $t4 -20($sp)
lw $t9 -8($sp)
sw $t9 -48($sp)
li $t9 3
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5930
addi $sp $sp 44
lw $ra -40($sp)
sw $v0 -24($sp)
move $t9 $v0
sw $t9 -48($sp)
la $t9 str_g6015
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5899
addi $sp $sp 44
lw $ra -40($sp)
sw $v0 -28($sp)
lw $a0 -20($sp)
lw $a1 -28($sp)
and $t9 $a0 $a1
beqz $t9 else_g6014
lw $t9 -4($sp)
sw $t9 -48($sp)
li $t9 3
sw $t9 -52($sp)
la $t9 str_g6016
sw $t9 -56($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5931
addi $sp $sp 44
lw $ra -40($sp)
jr $ra
b endif_g6014
else_g6014:
nop
endif_g6014:
lw $t9 -4($sp)
sw $t9 -48($sp)
li $t9 1
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5930
addi $sp $sp 44
lw $ra -40($sp)
sw $v0 -8($sp)
if_g6017:
lw $t9 -8($sp)
sw $t9 -48($sp)
la $t9 str_g6018
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5899
addi $sp $sp 44
lw $ra -40($sp)
move $t9 $v0
beqz $t9 else_g6017
lw $t9 -4($sp)
sw $t9 -48($sp)
li $t9 1
sw $t9 -52($sp)
la $t9 str_g6019
sw $t9 -56($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5931
addi $sp $sp 44
lw $ra -40($sp)
jr $ra
b endif_g6017
else_g6017:
nop
endif_g6017:
lw $t9 -4($sp)
sw $t9 -48($sp)
li $t9 4
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5930
addi $sp $sp 44
lw $ra -40($sp)
sw $v0 -8($sp)
if_g6020:
lw $t9 -8($sp)
sw $t9 -48($sp)
la $t9 str_g6021
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5899
addi $sp $sp 44
lw $ra -40($sp)
move $t9 $v0
beqz $t9 else_g6020
lw $t9 -4($sp)
sw $t9 -48($sp)
li $t9 4
sw $t9 -52($sp)
la $t9 str_g6022
sw $t9 -56($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5931
addi $sp $sp 44
lw $ra -40($sp)
jr $ra
b endif_g6020
else_g6020:
nop
endif_g6020:
if_g6023:
lw $t9 -8($sp)
sw $t9 -48($sp)
la $t9 str_g6024
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5899
addi $sp $sp 44
lw $ra -40($sp)
move $t9 $v0
beqz $t9 else_g6023
lw $t9 -4($sp)
sw $t9 -48($sp)
li $t9 4
sw $t9 -52($sp)
la $t9 str_g6025
sw $t9 -56($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5931
addi $sp $sp 44
lw $ra -40($sp)
jr $ra
b endif_g6023
else_g6023:
nop
endif_g6023:
lw $t9 -4($sp)
sw $t9 -48($sp)
li $t9 3
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5930
addi $sp $sp 44
lw $ra -40($sp)
sw $v0 -8($sp)
if_g6026:
lw $t9 -8($sp)
sw $t9 -48($sp)
la $t9 str_g6027
sw $t9 -52($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5899
addi $sp $sp 44
lw $ra -40($sp)
move $t9 $v0
beqz $t9 else_g6026
lw $t9 -4($sp)
sw $t9 -48($sp)
li $t9 3
sw $t9 -52($sp)
la $t9 str_g6028
sw $t9 -56($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5931
addi $sp $sp 44
lw $ra -40($sp)
jr $ra
b endif_g6026
else_g6026:
nop
endif_g6026:
if_g6029:
lw $t9 -4($sp)
sw $t9 -48($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5996
addi $sp $sp 44
lw $ra -40($sp)
sw $v0 -32($sp)
move $a0 $v0
seq $t9 $a0 0
beqz $t9 else_g6029
lw $t9 -4($sp)
sw $t9 -48($sp)
li $t9 1
sw $t9 -52($sp)
la $t9 str_g6030
sw $t9 -56($sp)
sw $ra -40($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -44($sp)
addi $sp $sp -44
jal func_g5931
addi $sp $sp 44
lw $ra -40($sp)
jr $ra
b endif_g6029
else_g6029:
lw $v0 -4($sp)
jr $ra
endif_g6029:
jr $ra
# func add_more_poetry
func_g6031:
if_g6032:
lw $a0 -12($sp)
seq $t9 $a0 0
beqz $t9 else_g6032
move $t7 $sp
lw $t7 0($t7)
lw $t7 0($t7)
lw $t9 -44($t7)
sw $t9 -68($sp)
la $t9 str_g6033
sw $t9 -72($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5913
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -16($sp)
move $t9 $v0
sw $t9 -68($sp)
lw $t9 -8($sp)
sw $t9 -72($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5913
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -20($sp)
move $t9 $v0
sw $t9 -68($sp)
la $t9 str_g6034
sw $t9 -72($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5913
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -24($sp)
move $t9 $v0
sw $t9 -68($sp)
move $t7 $sp
lw $t7 0($t7)
lw $t7 0($t7)
lw $t9 -44($t7)
sw $t9 -72($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5913
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -28($sp)
move $t9 $v0
sw $t9 -68($sp)
la $t9 str_g6035
sw $t9 -72($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5913
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -32($sp)
move $t9 $v0
sw $t9 -68($sp)
lw $t9 -8($sp)
sw $t9 -72($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5913
addi $sp $sp 64
lw $ra -60($sp)
jr $ra
b endif_g6032
else_g6032:
lw $a0 -12($sp)
li $a1 1
sub $t4 $a0 $a1
sw $t4 -36($sp)
lw $t9 -4($sp)
sw $t9 -68($sp)
lw $t9 -8($sp)
sw $t9 -72($sp)
lw $t9 -36($sp)
sw $t9 -76($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g6031
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -40($sp)
move $t9 $v0
sw $t9 -68($sp)
la $t9 str_g6036
sw $t9 -72($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5913
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -44($sp)
move $t9 $v0
sw $t9 -68($sp)
move $t7 $sp
lw $t7 0($t7)
lw $t7 0($t7)
lw $t9 -44($t7)
sw $t9 -72($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5913
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -48($sp)
move $t9 $v0
sw $t9 -68($sp)
la $t9 str_g6037
sw $t9 -72($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5913
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -52($sp)
move $t9 $v0
sw $t9 -68($sp)
lw $t9 -8($sp)
sw $t9 -72($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5913
addi $sp $sp 64
lw $ra -60($sp)
jr $ra
endif_g6032:
jr $ra
# func poetize
func_g5998:
la $t9 str_g6038
sw $t9 -24($sp)
lw $t9 -4($sp)
sw $t9 -28($sp)
lw $t9 -8($sp)
sw $t9 -32($sp)
sw $ra -16($sp)
la $t9 0($sp)
sw $t9 -20($sp)
addi $sp $sp -20
jal func_g6031
addi $sp $sp 20
lw $ra -16($sp)
jr $ra
jr $ra
# func generate_poetry
func_g5932:
la $t9 str_g6039
sw $t9 -68($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5911
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -4($sp)
while_g6040:
lw $t9 -4($sp)
sw $t9 -68($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5897
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -8($sp)
move $a0 $v0
li $a1 0
seq $t4 $a0 $a1
sw $t4 -12($sp)
lw $t9 -4($sp)
sw $t9 -68($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5925
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -16($sp)
lw $a0 -12($sp)
lw $a1 -16($sp)
or $t9 $a0 $a1
beqz $t9 endwhile_g6040
if_g6041:
lw $t9 -4($sp)
sw $t9 -68($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5897
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -20($sp)
move $a0 $v0
li $a1 0
seq $t9 $a0 $a1
beqz $t9 else_g6041
la $t9 str_g6042
sw $t9 -68($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5911
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -4($sp)
b endif_g6041
else_g6041:
la $t9 str_g6043
sw $t9 -68($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5911
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -4($sp)
endif_g6041:
b while_g6040
endwhile_g6040:
la $t9 str_g6044
sw $t9 -68($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5911
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -24($sp)
while_g6045:
lw $t9 -24($sp)
sw $t9 -68($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5927
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -28($sp)
move $a0 $v0
seq $t4 $a0 0
sw $t4 -32($sp)
lw $t9 -24($sp)
sw $t9 -68($sp)
la $t9 str_g6046
sw $t9 -72($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5899
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -36($sp)
lw $a0 -32($sp)
lw $a1 -36($sp)
or $t9 $a0 $a1
beqz $t9 endwhile_g6045
la $t9 str_g6047
sw $t9 -68($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5911
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -24($sp)
b while_g6045
endwhile_g6045:
lw $t9 -4($sp)
sw $t9 -68($sp)
sw $ra -60($sp)
la $t9 0($sp)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5997
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -4($sp)
if_g6048:
lw $t9 -4($sp)
sw $t9 -68($sp)
li $t9 1
sw $t9 -72($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5929
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -40($sp)
move $t9 $v0
sw $t9 -68($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5926
addi $sp $sp 64
lw $ra -60($sp)
move $t9 $v0
beqz $t9 else_g6048
la $t9 str_g6049
sw $t9 -44($sp)
b endif_g6048
else_g6048:
la $t9 str_g6050
sw $t9 -44($sp)
endif_g6048:
lw $t9 -24($sp)
sw $t9 -68($sp)
sw $ra -60($sp)
la $t9 0($sp)
lw $t9 0($t9)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5928
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -48($sp)
lw $t9 -4($sp)
sw $t9 -68($sp)
lw $t9 -48($sp)
sw $t9 -72($sp)
sw $ra -60($sp)
la $t9 0($sp)
sw $t9 -64($sp)
addi $sp $sp -64
jal func_g5998
addi $sp $sp 64
lw $ra -60($sp)
sw $v0 -52($sp)
move $a0 $v0
li $v0 4
syscall
li $a0 10
li $v0 11
syscall
jr $ra
main:
sw $ra -4($sp)
la $t9 0($sp)
sw $t9 -8($sp)
addi $sp $sp -8
jal func_g5932
addi $sp $sp 8
lw $ra -4($sp)
jr $ra
