  .data
true_ble: .asciiz "$1 <= $2\n"
false_ble: .asciiz "$1 > $2\n"


# ble $1 $2 label
  .text
main:
  addi $sp $sp -4
  sw $ra 0($sp)
test1:
  li $s1 1
  li $s2 1
  jal _ble   # expected log "$1 <= $2"
test2:
  li $s1 1
  li $s2 0
  jal _ble   # expected log "$1 > $2"
test3:
  li $s1 0
  li $s2 1
  jal _ble   # expected log "$1 <= $2"
end:
  lw $ra 0($sp)
  addi $sp $sp 4
  jr $ra

#-----ble $s1 $s2 label----
_ble:
  slt $t0 $s2 $s1
  beq $t0 $zero label
# -------------------------
else:
  li $v0 4
  la $a0 false_ble
  syscall
  jr $ra

label:
  li $v0 4
  la $a0 true_ble
  syscall
  jr $ra
