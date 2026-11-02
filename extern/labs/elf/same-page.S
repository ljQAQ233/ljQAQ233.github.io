println:
  push %rbp
  mov %rsp, %rbp

  sub $32, %rsp
  mov %rdi, %rax
  mov $10, %rcx
  lea 30(%rsp), %rsi
  movb $0, 1(%rsi)
  movb $'\n', (%rsi)
  movq $1, %r9

.Lconv:
  xor %rdx, %rdx
  div %rcx
  add $'0', %dl
  dec %rsi
  mov %dl, (%rsi)
  inc %r9
  test %rax, %rax
  jnz .Lconv

  movq $1, %rax
  mov $1, %rdi
  mov %r9, %rdx
  syscall

  leave
  ret

  .text
  .global _start
_start:
  mov int1, %rdi
  call println
  
  mov int2, %rdi
  call println

  movq $60, %rax
  xorq %rdi, %rdi
  syscall

  .section .d1, "aw"
int1: .quad 123456789
  .section .d2, "aw"
int2: .quad 987654321

