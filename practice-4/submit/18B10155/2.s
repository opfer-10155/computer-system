  .data
input_message: .asciiz "length = "
output_message: .asciiz "sum = "

  .text
main:
  addi $sp $sp -4
  sw $ra 0($sp)
  li $v0 4              # print message
  la $a0 input_message
  syscall
  li $v0 5              # input array_length
  syscall
  move $t0 $v0
  move $a0 $v0
  jal create_array
  move $a0 $v0
  move $a1 $t0
  jal calc_sum
  move $t1 $v0
  li $v0 4              # print message
  la $a0 output_message
  syscall
  li $v0 1              # print sum
  move $a0 $t1
  syscall

  lw $ra 0($sp)
  addi $sp $sp 4
  jr $ra

create_array:
  addi $sp $sp -12
  sw $t0 0($sp)
  sw $t1 4($sp)
  sw $t2 8($sp)
  move $t0 $a0     # $t0 = $a0
  add $a0 $a0 $a0  # $a0 = $a0 * 4
  add $a0 $a0 $a0
  li $v0 9         # $v0 = malloc($a0*4)
  syscall
  move $a0 $t0
  move $t0 $v0     # $t0 = $v0
  li $t2 0         # i = 0
LOOP1:
  bge $t2 $a0 end1 # if (i >= $a0) go to end
  li $v0 5         # read_int
  syscall
  add $t1 $t2 $t2  # $t1 = i * 4 + $t0
  add $t1 $t1 $t1
  add $t1 $t0 $t1
  sw $v0 0($t1)    # $t0[i] = read_int
  addi $t2 $t2 1   # i++
  j LOOP1
end1:
  move $v0 $t0
  lw $t2 8($sp)
  lw $t1 4($sp)
  lw $t0 0($sp)
  add $sp $sp 12
  jr $ra

calc_sum:
  addi $sp $sp -8
  sw $t0 0($sp)
  sw $t1 4($sp)
  li $v0 0            # sum = 0
  li $t0 0            # i = 0
LOOP2:
  bge $t0 $a1 end2    # if (i >= $a1) go to end
  add $t1 $t0 $t0     # $t1 = i * 4 + $a0
  add $t1 $t1 $t1
  add $t1 $t1 $a0
  lw $t1 0($t1)       # $t1 = $a0[i]
  add $v0 $v0 $t1     # sum += $t1
  addi $t0 $t0 1      # i++
  j LOOP2
end2:
  lw $t1 4($sp)
  lw $t0 0($sp)
  addi $sp $sp 8
  jr $ra
