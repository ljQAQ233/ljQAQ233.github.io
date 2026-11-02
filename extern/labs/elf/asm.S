  .text
  .globl _start
_start:
  movq $1, %rax
  movq $1, %rdi
  leaq msg(%rip), %rsi
  movq $len, %rdx
  syscall

  movq $60, %rax
  xorq %rdi, %rdi
  syscall

  .data
msg:
  .ascii "Hello world!\n"
len = . - msg
