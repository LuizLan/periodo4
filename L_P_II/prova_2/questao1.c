#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

/*
(Questão 1 - 5,0)
Escreva um programa em C que simule um sistema de detecção de vazamento em uma represa.
O programa deve usar threads POSIX e espera ocupada para detectar mudanças em uma variável 
que representa o nível de água da represa (valor inicial: 1000 litros). 
O nível de água é modificado por um conjunto de 5 threads. 
Cada thread receberá um valor aleatório do quanto incrementará no nível do reservatório 
(entre 10 e 100 litros) e dormirá um tempo aleatório (entre 0 e 300ms) entre cada incremento. 
Quando o nível de água atingir 5000 litros, essas threads devem ser bloqueadas até que a thread principal 
garanta que o nível do reservatório foi reestabelecido para 1000 litros (e depois dormir 200ms). 
Deve ser utilizada espera ocupada em todos os casos e funções atômicas para 
modificação do nível do reservatório.
*/

#define QTD_THREADS 5

int nivel_agua = 1000;
sem_t semaforo;

void* incrementa(void* p) { // funcao para incrementar o nivel da agua
    srand(getpid()+ (long)p); //seed unica para cada thread, para ficar mais randomizado ainda
    int* valor = &nivel_agua; // ponteiro para o nivel da agua, para que possa ser usada a funcao atomica
    int incremento = rand() % 91 + 10; // definindo qual sera o incremento aleatorio para essa thread
    int tempo = rand() % 301; // definindo o tempo aleatorio para essa thread
    while(1) {
        __sync_fetch_and_add(valor, incremento); //funcao atomica para aumentar o valor do nivel da agua
        printf("[T%ld] Incremento: %d, nivel: %d\n", (long)p, incremento, nivel_agua); //mostra o nivel do aumento da thread e o nivel total da agua
        usleep(tempo);
        if (nivel_agua >= 5000) { //se estiver acima do limite espera a main voltar o nivel da agua para 1000
            sem_wait(&semaforo);
        }else{
            sem_post(&semaforo);
        }
    }
}

int main(void){
    time_t t;
    pthread_t threads[QTD_THREADS];

    sem_init(&semaforo, 0, 1); //iniciando semaforo
    srand(time(&t));

    for(long i = 0; i < QTD_THREADS; i++) {
        pthread_create(&threads[i], NULL, incrementa, (void*)i); //iniciando as threads
    }

    while(1){
        while(nivel_agua >= 5000){ //se o nivel da agua ultrapassar o limite 
            sem_wait(&semaforo); //pausa as threads
            nivel_agua = 1000; //reduz o nivel para 1000
            printf("[P] Nivel reestabelecido: %d\n", nivel_agua); //mostra que foi reduzido
            if(nivel_agua == 1000){ //retoma as atividades
                sem_post(&semaforo);
                usleep(200);
            }
        }
    }

    return 0;
}