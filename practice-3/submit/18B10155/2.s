  .data
A: .word 1 2 3 4
B: .word 5 6 7 8

  .text
# i = 0
# while(i <= 3) {
#   print(A[i] + B[3-i])
#   i++
# }
main:
  li $t0 0            # i = 0
LOOP_1:
  li $t1 3            # $t1 = 3
  bgt $t0 $t1 end     # if i > 3 goto end
  li $a1 4            # $t1 = i * 4
  mult $t0 $a1
  mflo $t1
  lw $t2 A($t1)       # $t2 = A[i]
  li $t3 3
  sub $t3 $t3 $t0     # $t3 = 3 - i
  mult $t3 $a1        # $t3 *= 4
  mflo $t3
  lw $t4 B($t3)       # $t4 = B[3-i]
  add $t5 $t4 $t2     # $t5 = A[i] + B[3-i]
  li $v0 1
  addi $a0 $t5 0
  syscall
  addi $t0 1
  jr LOOP_1
end:
  jr $ra
