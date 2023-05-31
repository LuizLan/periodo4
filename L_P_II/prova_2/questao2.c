#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

/*
(Questão 2 - 5,0)
Escreva um programa em C/C++ que simule o funcionamento de um sistema de pedágio em uma rodovia. 
O programa deve usar threads para representar os veículos que passam pelo pedágio e deve explorar a solução do problema da seção crítica 
(solucionando com trava ou semáforo) e sincronismo condicional (usando barreira).
 
Cada veículo deve escolher aleatoriamente uma das cabines de pedágio para passar e deve esperar sua vez para pagar o pedágio. 
Quando um veículo paga o pedágio, ele deve incrementar o valor total arrecadado pelo pedágio. 
O programa deve garantir que apenas um veículo por vez possa pagar o pedágio em cada cabine 
(usando trava ou semáforo para solucionar o problema da seção crítica).
 
Além disso, o programa deve usar uma barreira para sincronizar os veículos de forma que eles 
só possam sair do pedágio depois que todos os veículos tenham pago o pedágio. 
Depois que todos os veículos saírem do pedágio, o programa deve imprimir o valor total arrecadado pelo pedágio.
 
O programa deve terminar quando todos os veículos tiverem passado pelo pedágio.
*/

#define QTD_VEICULOS 2000
#define QTD_CABINES 100
#define VALOR 5

pthread_barrier_t barreira;
sem_t semaforo[QTD_CABINES];

int valor_arrecadado = 0;

void* pedagio(void* p){ //thread que cada veiculo vai executar, enquanto estiver no pedagio
    int* arrecadado = &valor_arrecadado; //ponteiro para a funcao atomica
    int cabine = rand() % QTD_CABINES; //escolhe para qual cabine vai cada carro
    int tempo = rand() % 1001; // tempo ficcional que cada carro passa em uma cabine
    printf("[V%ld] Cabine: %d\n", (long)p, cabine);
    usleep(tempo); //simula o tempo na cabine
    sem_wait(&semaforo[cabine]); // para cada cabine existe um semaforo espicifico, ja que cada carro nao pode pagar na mesma cabine, mas podem pagar ao mesmo tempo em cabines diferentes
    __sync_fetch_and_add(arrecadado, VALOR); //funcção atomica já que mais de um veiculo pode pagar ao mesmo tempo, por meio de cabines diferentes
    printf("[V%ld] Valor arrecadado: %d, cabine: %d\n", (long)p, valor_arrecadado, cabine); //mostra o carro, o valor total atual e em qual cabine ele foi
    sem_post(&semaforo[cabine]); //libera a cabine para o proximo carro
    pthread_barrier_wait(&barreira); //espera na barreira para que possa encerrar o programa
}

int main(void){
    time_t t;
    pthread_t threads[QTD_VEICULOS];

    pthread_barrier_init(&barreira, NULL, QTD_VEICULOS + 1); // inicia a barreira com a quantidade de carros mais a main

    for (int i = 0; i < QTD_CABINES; i++){
        sem_init(&semaforo[i], 0, 1); //inicia os semaforos das cabines
    }
    for (long i = 0; i < QTD_VEICULOS; i++){
        pthread_create(&threads[i], NULL, pedagio, (void*)i); // cria as threads
    }

    pthread_barrier_wait(&barreira); //esperando todos os veiculos sairem

    printf("[P]Valor total arrecadado: %d\n", valor_arrecadado); //mostra o valor total arrecadado e encerra o programa
    printf("[P]Fim do programa\n");
    
    return 0;
}