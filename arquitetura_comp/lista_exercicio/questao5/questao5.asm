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

.code
start:
    mov ebx, 11
    mov ecx, 1000
for_lace:
    mov eax, ecx
    xor edx, edx
    div ebx 
    cmp edx, 5
    je show
mid_lace:
    inc ecx
    cmp ecx, 1999
    jbe for_lace
    jmp end_program

show:
    push ecx
    printf("%d\n", ecx)
    pop ecx
    jmp mid_lace

end_program:
    invoke ExitProcess, 0
end start