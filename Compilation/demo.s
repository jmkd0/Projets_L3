.data
msg1: .asciiz "Enter a number: "

.text


li $v0,4
la $a0,msg1

while:

syscall
li $v0,5
syscall
bgt $v0,10,print
li $v0,10
syscall

j while

print:
li $v0,1
move $a0,$v0
syscall

j while
