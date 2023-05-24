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
    a_num dd 10

.code
start:
;checar algarismo menos significativo
    mov eax, a_num
    and eax, 1, XXXXXXX AND 00000001, compara o ultimo bit com 1, se 1 = impar, 0 = par
    cmp eax, 0
    je eh_par
    printf("%d eh impar\n", a_num)
    jmp end_program
eh_par:
    printf("%d eh par\n", a_num)	

end_program:
    invoke ExitProcess, 0
end start