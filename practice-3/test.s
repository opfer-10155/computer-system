  .data
str: .asciiz "unko"

  .text
main:
  li $v0 4

hoge:
  la $a0 str
  syscall
  jr $ra
