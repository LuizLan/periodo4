.686
.model flat, stdcall
option casemap:none

include \masm32\include\windows.inc
include \masm32\include\kernel32.inc
include \masm32\include\msvcrt.inc
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\msvcrt.lib

.data ?
    outputHandle dd ?
    write_count dd ?

.data
    menu1 db "1. Codificar", 0ah, 0h
    menu2 db "2. Decodificar", 0ah, 0h
    menu3 db "3. Sair", 0ah, 0h
    

.code
start:
    push STD_OUTPUT_HANDLE
    call GetStdHandle
    mov outputHandle, eax

menu_lace:
    invoke WriteConsoleA, outputHandle, addr menu1, sizeof menu1, addr write_count, NULL
    invoke WriteConsoleA, outputHandle, addr menu2, sizeof menu2, addr write_count, NULL
    invoke WriteConsoleA, outputHandle, addr menu3, sizeof menu3, addr write_count, NULL








end_program:
    invoke ExitProcess, 0
end start