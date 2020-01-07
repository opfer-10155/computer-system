  .data
A: .word 1 2 3
B: .word 7 6 5
L: .word 3  # length of array

  .text
# i = 0
# while(i < L) {
#   print(A[i] + B[L-1-i])
#   i++
# }
main:
  li $t0 0            # i = 0
LOOP_1:
  lw $t1 L($zero)     # $t1 = L
  bge $t0 $t1 end     # if i >= L goto end
  li $a1 4            # $t1 = i * 4
  mult $t0 $a1
  mflo $t1
  lw $t2 A($t1)       # $t2 = A[i]
  lw $t3 L($zero)     # $t3 = L
  addi $t3 $t3 -1     # $t3 = L - 1
  sub $t3 $t3 $t0     # $t3 = L - 1 - i
  mult $t3 $a1        # $t3 *= 4
  mflo $t3
  lw $t4 B($t3)       # $t4 = B[L-i]
  add $t5 $t4 $t2     # $t5 = A[i] + B[L-i]
  li $v0 1
  addi $a0 $t5 0
  syscall             # print($t5)
  addi $t0 1
  jr LOOP_1
end:
  jr $ra
