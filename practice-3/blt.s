  .data
true_blt: .asciiz "$1 < $2\n"
false_blt: .asciiz "$1 >= $2\n"

  .text

main:
  addi $sp $sp -4
  sw $ra 0($sp)
test1:
  li $s1 1
  li $s2 1
  jal _blt   # expected log "$1 >= $2"
test2:
  li $s1 1
  li $s2 0
  jal _blt   # expected log "$1 >= $2"
test3:
  li $s1 0
  li $s2 1
  jal _blt   # expected log "$1 < $2"
end:
  lw $ra 0($sp)
  addi $sp $sp 4
  jr $ra

#-----blt $s1 $s2 label----
_blt:
  slt $t0 $s1 $s2
  bne $t0 $zero label
# -------------------------
else:
  li $v0 4
  la $a0 false_blt
  syscall
  jr $ra

label:
  li $v0 4
  la $a0 true_blt
  syscall
  jr $ra
