#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

/*
(Questão 3 - 4,0)
Faça um programa em C/C++ que implemente uma solução para o problema do buffer compartilhado. 
Com um buffer compartilhado de 64 chars, 
o Programa deverá implementar duas funções:
 
	- produtor() - gera um caractere alfanumérico aleatório e o deposita
	no buffer; exibe o valor e a posição no buffer na tela; dorme 300ms;
	repete;
 
	- consumidor() - captura um dos valores disponíveis no buffer 
	compartilhado e armazena em um arquivo; dorme um tempo aleatório 
	entre 50ms e 200ms; repete;
 
A função produtor deverá ser realizada por uma thread; 
já a função consumidor deverá ser realizada por três (5) threads. 
Cada consumidor armazena as informações em um buffer diferente (de tamanho 64) 
e todas as threads devem armazenar todos os valores gerados pelo produtor. 
 
Use semáforos (biblioteca semaphore.h) para sincronizar o acesso ao buffer  compartilhado, de forma que todos os números gerados pelo produtor sejam consumidos uma vez, evitando qualquer problema ao ler ou escrever no buffer. Quando o buffer do consumidor estiver completo, o programa deverá exibir o seu contaúdo. Quando o buffer for consumido 2 vezes (ou seja, quando o produtor tiverem gerado 128 caracteres e estes forem consumidos por TODOS os consumidores) finalize o programa.
*/

#define BUFFER_SIZE 64
#define QTD_CONS 5

char buffer[BUFFER_SIZE];
sem_t empty, full, mutex;
pthread_barrier_t barreira;

void* funcao_produtor(void* p) {
    int gerado = 0;
    int rear = 0;

    while(1){
        char c = 'A' + rand() % 26;
        buffer[rear] = c;
        rear = (rear + 1) % BUFFER_SIZE;
        printf("[P] %c (%d)\n", c, rear);
        gerado++;
        usleep(150);
        if(gerado == 64){
            sem_post(&full);
            sem_wait(&empty);
        }
        if (gerado == 128){
            sem_post(&full);
            sem_wait(&empty);
            printf("[P] Fim do produtor\n");
            pthread_exit(0);
        }   
    }
}

void* funcao_consumidor(void* p){
    long id = (long)p;
    char arqnome[15];
    char buffer_cons[BUFFER_SIZE];
    int consumido = 0;
    int front = 0;

    sprintf(arqnome, "thread%ld.txt", id);

    FILE* arquivo = fopen(arqnome, "a+");

    while (1) {
        char c = buffer[front];
        front = (front + 1) % BUFFER_SIZE;
        printf("[C-%ld] %c (%d)\n", id, c, front);
        fprintf(arquivo, "%c", c);
        int dormir = 30 + rand() % 71;
        consumido++;
        if(consumido == 64){
            printf("[C-%ld] Buffer cheio\n", id);
            pthread_barrier_wait(&barreira);
            sem_post(&empty);
            sem_wait(&full);
        }
        if (consumido == 128) {
            printf("[C-%ld] Fim do consumidor\n", id);
            pthread_barrier_wait(&barreira);
            fclose(arquivo);
            exit(0);
        }
        usleep(dormir);
    }
    return NULL;
}  

int main(){
    pthread_t produtor;
    pthread_t consumidores[QTD_CONS];
    time_t t;

    srand((unsigned) time(&t));

    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 1);
    sem_init(&mutex, 0, 1);
    pthread_barrier_init(&barreira, NULL, QTD_CONS); // inicia a barreira com a quantidade de carros mais a main

    pthread_create(&produtor, NULL, funcao_produtor, NULL);

    for (long i = 0; i < QTD_CONS; i++) {
        pthread_create(&consumidores[i], NULL, funcao_consumidor, (void*)i);
    }

    pthread_join(produtor, NULL);

    for (int i = 0; i < QTD_CONS; i++) {
        pthread_join(consumidores[i], NULL);
    }
    return 0;
}