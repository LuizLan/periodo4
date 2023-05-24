.686
.model flat, stdcall
option casemap:none

include \masm32\include\windows.inc
include \masm32\include\kernel32.inc
include \masm32\include\msvcrt.inc
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\msvcrt.lib
include \masm32\macros\macros.asm

.data
    num1 dd 30
    num2 dd 20

.code 
start:
    mov eax, num2
    cmp num1, eax
    jg num1_greater
    printf("num1 is less or equal than num2, valor: %d\n", num2)
    jmp end_program
num1_greater:
    printf("num1 is greater than num2, valor: %d\n", num1)
end_program:
    invoke ExitProcess, 0
end start