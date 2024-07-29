section .bss
  buffer resb 64

section .data
  buffer_size dq 0
  chvar dq '!'

section .text

global _print
global _operator_addition
global _operator_subtraction
global _operator_multiplication
global _operator_division
global _operator_modulus
global _operator_assignment

%macro add_char 1
  mov qword [chvar], %1
  lea rdi, [buffer]
  mov rsi, chvar
  add rdi, [buffer_size]
  movsb
  inc qword [buffer_size]
%endmacro

%macro print_buffer 2 ;args: buffer, buffer_size
  mov r8, rax
  mov rax, 1
  mov rdi, 1
  mov rdx, [%2]
  mov rsi, %1
  mov qword [%2], 0 ;reset buffer_size so that buffer can be used again
  syscall
  mov rax, r8
%endmacro

%macro reverse_buffer 2 ;args: buffer, buffer_size
  lea rsi, [%1]
  lea rdi, [%1]
  add rdi, [%2]
  dec rdi
reverse_loop%1:
  cmp rsi, rdi
  jge reverse_done%1
  mov al, [rsi]
  mov bl, [rdi]
  mov [rdi], al
  mov [rsi], bl
  inc rsi
  dec rdi
  jmp reverse_loop%1
reverse_done%1:
%endmacro

_print: ;the integer to print must be stored on the stack
  mov rax, [rsp+8]
  cmp rax, 0
  je _zero
  test rax, rax
  js _negative
_main_loop:
  mov rcx, 10
  xor rdx, rdx
  idiv rcx
  add rdx, '0'
  add_char rdx
  cmp rax, 0
  jg _main_loop
  reverse_buffer buffer, buffer_size
  add_char 10
  print_buffer buffer, buffer_size
  ret
_zero:
  add_char '0'
  add_char 10
  print_buffer buffer, buffer_size
  ret
_negative: 
  add_char '-'
  print_buffer buffer, buffer_size
  neg rax
  jmp _main_loop

_operator_addition:
  pop rcx
  mov rax, [rsp+8]
  mov rbx, [rsp]
  add rsp, 16
  add rax, rbx
  push rax
  jmp rcx

_operator_subtraction:
  pop rcx
  mov rax, [rsp+8]
  mov rbx, [rsp]
  add rsp, 16
  sub rax, rbx
  push rax
  jmp rcx

_operator_multiplication:
  pop rcx
  mov rax, [rsp]
  mov rbx, [rsp+8]
  add rsp, 16
  imul rax, rbx
  push rax
  jmp rcx

_operator_division:
  pop rcx
  mov rax, [rsp+8]
  mov rbx, [rsp]
  add rsp, 16
  cqo
  idiv rbx
  push rax
  jmp rcx

_operator_modulus:
  pop rcx
  mov rax, [rsp+8]
  mov rbx, [rsp]
  add rsp, 16
  cqo
  idiv rbx
  push rdx
  jmp rcx

_operator_assignment:
  pop rcx
  mov rax, [rsp+8]
  mov rbx, [rsp]
  add rsp, 16
  mov [rax], rbx
  push [rax]
  jmp rcx
