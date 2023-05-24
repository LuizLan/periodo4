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
    my_array dw 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

.code
start:
    xor ebx, ebx
    xor ecx, ecx
start_lace:
    add bx, my_array[ecx*2]
    inc ecx
    cmp ecx, 10
    jb start_lace
    
    printf("o resultado do somatorio eh %d\n", ebx)

end_program:
    invoke ExitProcess, 0
end start