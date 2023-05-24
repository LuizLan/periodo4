.686
.model flat, stdcall
option casemap:none

include \masm32\include\windows.inc
include \masm32\include\kernel32.inc
include \masm32\include\msvcrt.inc
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\msvcrt.lib
include \masm32\macros\macros.asm

.code
start:
    xor eax, eax
    mov ecx, 1
laco_somatorio:
    add eax, ecx
    inc ecx
    cmp ecx, 100
    jle laco_somatorio
    printf("Somatorio: %d\n", eax)
    invoke ExitProcess, 1
end start