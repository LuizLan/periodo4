.686
.model flat, stdcall
option casemap:none

include \masm32\include\windows.inc
include \masm32\include\kernel32.inc
include \masm32\include\masm32.inc
include \masm32\include\msvcrt.inc
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\msvcrt.lib
includelib \masm32\lib\masm32.lib

.data?
    fileHandleInput HANDLE ?
    fileHandleOutput HANDLE ?

    outputHandle dd ?
    inputHandle dd ?
    console_count dd ?
    string_size dd ?
    readCount dd ?

    menuOptString db 50 dup(?)
    inputFile db 50 dup(?)
    outputFile db 50 dup(?)
    keyString db 50 dup(?)
    inputString db 512 dup(?)

    keyInt dword ?
    menuOptionInt dword ?
    
.data
    menu1 db "1. Codificar", 0ah, 0h
    menu2 db "2. Decodificar", 0ah, 0h
    menu3 db "3. Sair", 0ah, 0h

    inputFilePrompt db "Digite o nome do arquivo de entrada: ", 0ah, 0h
    outputFilePrompt db "Digite o nome do arquivo de saida: ", 0ah, 0h
    keyInputPrompt db "Digite a chave de codificacao: ", 0ah, 0h

.code
start:
    invoke GetStdHandle, STD_INPUT_HANDLE
    mov inputHandle, eax
    invoke GetStdHandle, STD_OUTPUT_HANDLE
    mov outputHandle, eax
    jmp menu_lace

codificar:
    

inputMenu:
    invoke WriteConsoleA, outputHandle, addr inputFilePrompt, sizeof inputFilePrompt, addr console_count, NULL
    invoke ReadConsoleA, inputHandle, addr inputFile, sizeof inputFile, addr console_count, NULL
    mov esi, offset inputFile
 tratamentoStringFileInput:
    mov al, [esi] ; Mover caractere atual para al
    inc esi ; Apontar para o proximo caractere
    cmp al, 13 ; Verificar se eh o caractere ASCII CR - FINALIZAR
    jne tratamentoStringFileInput ; Se nao for, continuar
    dec esi ; Apontar para caractere anterior
    xor al, al ; ASCII 0
    mov [esi], al ; Inserir ASCII 0 no lugar do ASCII CR

    invoke StrLen, addr inputFile
    mov string_size, eax

    invoke WriteConsoleA, outputHandle, addr inputFile, string_size, addr console_count, NULL
    
    invoke CreateFile, addr inputFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
    mov fileHandleInput, eax

    invoke ReadFile, fileHandleInput, addr inputString, 512, addr readCount, NULL
    invoke WriteConsoleA, outputHandle, addr inputString, readCount, addr console_count, NULL
    
    invoke WriteConsoleA, outputHandle, addr outputFilePrompt, sizeof outputFilePrompt, addr console_count, NULL
    invoke ReadConsoleA, inputHandle, addr outputFile, sizeof outputFile, addr console_count, NULL
    
    mov esi, offset outputFile
tratamentoStringFileOutput:
    mov al, [esi] ; Mover caractere atual para al
    inc esi ; Apontar para o proximo caractere
    cmp al, 13 ; Verificar se eh o caractere ASCII CR - FINALIZAR
    jne tratamentoStringFileOutput ; Se nao for, continuar
    dec esi ; Apontar para caractere anterior
    xor al, al ; ASCII 0
    mov [esi], al ; Inserir ASCII 0 no lugar do ASCII CR

    invoke StrLen, addr outputFile
    mov string_size, eax

    invoke WriteConsoleA, outputHandle, addr outputFile, string_size, addr console_count, NULL

    invoke CreateFile, addr outputFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
    mov fileHandleOutput, eax

    invoke WriteConsoleA, outputHandle, addr keyInputPrompt, sizeof keyInputPrompt, addr console_count, NULL
    invoke ReadConsoleA, inputHandle, addr keyString, sizeof keyString, addr console_count, NULL
    mov esi, offset keyString
tratamentoStringKey:
    mov al, [esi] ; Mover caractere atual para al
    inc esi ; Apontar para o proximo caractere
    cmp al, 13 ; Verificar se eh o caractere ASCII CR - FINALIZAR
    jne tratamentoStringKey ; Se nao for, continuar
    dec esi ; Apontar para caractere anterior
    xor al, al ; ASCII 0
    mov [esi], al ; Inserir ASCII 0 no lugar do ASCII CR

    invoke StrLen, addr keyString
    mov string_size, eax

    invoke WriteConsoleA, outputHandle, addr keyString, string_size, addr console_count, NULL

    ;cmp menuOptionInt, 1
    ;je codificar
    ;cmp menuOptionInt, 2
    ;je decodificar

    jmp end_program

menu_lace:
    invoke WriteConsoleA, outputHandle, addr menu1, sizeof menu1, addr console_count, NULL
    invoke WriteConsoleA, outputHandle, addr menu2, sizeof menu2, addr console_count, NULL
    invoke WriteConsoleA, outputHandle, addr menu3, sizeof menu3, addr console_count, NULL
    invoke ReadConsoleA, inputHandle, addr menuOptString, sizeof menuOptString, addr console_count, NULL
    
    mov esi, offset menuOptString ; Armazenar apontador da string em esi

tratamentoMenu:
    mov al, [esi] ; Mover caractere atual para al
    inc esi ; Apontar para o proximo caractere
    cmp al, 13 ; Verificar se eh o caractere ASCII CR - FINALIZAR
    jne tratamentoMenu ; Se nao for, continuar
    dec esi ; Apontar para caractere anterior
    xor al, al ; ASCII 0
    mov [esi], al ; Inserir ASCII 0 no lugar do ASCII CR

checkOption:
    invoke atodw, addr menuOptString
    mov menuOptionInt, eax

    cmp menuOptionInt, 1
    je inputMenu
    cmp menuOptionInt, 2
    je inputMenu
    cmp menuOptionInt, 3
    jmp end_program


end_program:
    invoke ExitProcess, 0
end start