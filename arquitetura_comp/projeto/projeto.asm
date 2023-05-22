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
    fileHandleInput HANDLE ?; handle para o arquivo de entrada
    fileHandleOutput HANDLE ?; handle para o arquivo de saida

    outputHandle dd ?; handle do prompt para output
    inputHandle dd ?; handle do prompt para input
    console_count dd ?; count para o prompt
    string_size dd ?; tamanho da string para WriteConsoleA
    fileCount dd ?; count para o arquivo

    menuOptString db 10 dup(?); string para a opcao do menu
    inputFile db 100 dup(?); string para o nome do arquivo de entrada
    outputFile db 100 dup(?); string para o nome do arquivo de saida
    keyString db 10 dup(?); string para a chave de codificacao

    keyInt dword ?; chave de codificacao em dword
    menuOptionInt dword ?; opcao do menu em dword
    
.data
    bufferSize equ 512; definicao do bufferSize
    buffer db bufferSize dup(?); buffer para leitura do arquivo
    outputBuffer db bufferSize dup(?); buffer para escrita no arquivo

    ; strings para visualizacao dos menus

    menu1 db "1. Codificar", 0ah, 0h
    menu2 db "2. Decodificar", 0ah, 0h
    menu3 db "3. Sair", 0ah, 0h

    inputFilePrompt db "Digite o nome do arquivo de entrada: ", 0ah, 0h
    outputFilePrompt db "Digite o nome do arquivo de saida: ", 0ah, 0h
    keyInputPrompt db "Digite a chave de codificacao: ", 0ah, 0h

.code
start:
    invoke GetStdHandle, STD_INPUT_HANDLE; obtendo handle do prompt para input
    mov inputHandle, eax
    invoke GetStdHandle, STD_OUTPUT_HANDLE; obtendo handle do prompt para output
    mov outputHandle, eax
    jmp menu_lace; indo para o menu

codificar:

invoke ReadFile, fileHandleInput, addr buffer, bufferSize, addr fileCount, NULL
cmp fileCount, 0; checa se o arquivo esta vazio
je menu_lace; se estiver volta para o menu

xor ecx, ecx; limpa ecx, servira de flag para navegar os buffer e checar se ja saiu do loop
mov eax, keyInt
mov dl, al ; move a chave para dl, para poder ser somada nos caracteres

increase_loop:
    mov eax, [offset buffer + ecx]; move caractere atual para eax
    mov bl, al; 
    add bl, dl; soma a chave no caractere atual
    mov al, bl;
    mov [offset outputBuffer + ecx], eax; joga o caractere atual para o buffer de saida

    inc ecx; incrementa eax

    cmp ecx, fileCount; checa se ja chegou ao fim da parte lida do arquivo
    jne increase_loop; se nao chegou, volta para o inicio do loop

invoke WriteFile, fileHandleOutput, addr outputBuffer, fileCount, addr fileCount, NULL; escreve a string alterada no arquivo de saida

cmp fileCount, bufferSize; checa se o buffer estava cheio, se estiver volta para o inicio do loop de leitura
je codificar

invoke CloseHandle, fileHandleInput
invoke CloseHandle, fileHandleOutput
jmp menu_lace

decodificar:

invoke ReadFile, fileHandleInput, addr buffer, bufferSize, addr fileCount, NULL; le o arquivo de entrada ate o limite do buffer
cmp fileCount, 0; checa se o arquivo esta vazio
je menu_lace; se estiver volta para o menu

xor ecx, ecx; limpa ecx, servira de flag para navegar os buffer e checar se ja saiu do loop
mov eax, keyInt
mov dl, al; move a chave para dl, para poder ser subtraida nos caracteres

decrease_loop:
    mov eax, [offset buffer + ecx]; move caractere atual para eax
    mov bl, al;
    sub bl, dl; subtrai a chave no caractere atual
    mov al, bl;
    mov [offset outputBuffer + ecx], eax; joga o caractere atual para o buffer de saida

    inc ecx; incrementa ecx

    cmp ecx, fileCount; checa se ja chegou ao fim da parte lida do arquivo
    jne decrease_loop; se nao chegou, volta para o inicio do loop

invoke WriteFile, fileHandleOutput, addr outputBuffer, fileCount, addr fileCount, NULL; escreve a string alterada no arquivo de saida

cmp fileCount, bufferSize; checa se o buffer estava cheio, se estiver volta para o inicio do loop de leitura
je codificar

invoke CloseHandle, fileHandleInput
invoke CloseHandle, fileHandleOutput
jmp menu_lace

inputMenu: ;menu para leitura dos nomes dos arquivos e da chave escolhida pelo usuario

    ;le e trata o nome do arquivo de entrada dado pelo usuario

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

    invoke CreateFile, addr inputFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL ;abre o arquivo de entrada no modo de leitura
    mov fileHandleInput, eax

    ;le e trata o nome do arquivo de saida dado pelo usuario

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

    invoke CreateFile, addr outputFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ;cria o arquivo de saida no modo de escrita
    mov fileHandleOutput, eax
    

    ;le e trata a chave de codificacao dada pelo usuario

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

    invoke atodw, addr keyString ; tranforma a chave dada pelo usuario em dword
    mov keyInt, eax

    mov eax, menuOptionInt ; verifica se o usuario escolheu codificar ou decodificar
    cmp eax, 1
    je codificar
    cmp eax, 2
    je decodificar

    jmp end_program

menu_lace: ; Menu de opcoes de criptografar, descritografar ou sair
    invoke WriteConsoleA, outputHandle, addr menu1, sizeof menu1, addr console_count, NULL
    invoke WriteConsoleA, outputHandle, addr menu2, sizeof menu2, addr console_count, NULL ; exibem as opcoes
    invoke WriteConsoleA, outputHandle, addr menu3, sizeof menu3, addr console_count, NULL
    invoke ReadConsoleA, inputHandle, addr menuOptString, sizeof menuOptString, addr console_count, NULL ; le a escolha do usuario
    
    mov esi, offset menuOptString ; Armazenar apontador da string em esi

tratamentoMenu: ;faz o tratamento de erro no input do usuario
    mov al, [esi] ; Mover caractere atual para al
    inc esi ; Apontar para o proximo caractere
    cmp al, 13 ; Verificar se eh o caractere ASCII CR - FINALIZAR
    jne tratamentoMenu ; Se nao for, continuar
    dec esi ; Apontar para caractere anterior
    xor al, al ; ASCII 0
    mov [esi], al ; Inserir ASCII 0 no lugar do ASCII CR

checkOption:
    invoke atodw, addr menuOptString ; tranforma a string em dw
    mov menuOptionInt, eax

    cmp eax, 1 ; checa qual foi a escolha do usuario
    je inputMenu
    cmp eax, 2
    je inputMenu
    cmp eax, 3
    jmp end_program


end_program:
    invoke ExitProcess, 0
end start