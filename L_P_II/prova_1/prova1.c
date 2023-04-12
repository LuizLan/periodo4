#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>

#define QTD_PARAM 4

int qtdThread = 0;
int qtdProc = 0;
long tamMax = 0;

void* randNum(){ //função que gera um numero aleatorio baseado no valor maximo dado

    long randomNumLoc;
    
    randomNumLoc = (rand()%tamMax) + 1;
    
    return(void*)randomNumLoc; //retorna o numero aleatorio em void* para que possa ser recebido por thread_join
}

int main(int argc, char** argv){ 
    time_t t;
    clock_t comeco, fim;//marcar o tempo de criacao das threads e processos
    float tempoTot = 0;

    pthread_t *threads; //variavel usada para thread
    
    int *pids, pidOrig = getpid(); //variaveis que serao usadas em processo

    float totalThread = 0, totalProc = 0; //variaveis para funcionamento geral do programa
    long resThread, resProc;

    if (argc != QTD_PARAM) {
		printf("use: %s <qtd_Thread> <qtd_Proc> <tam_Max> \n", argv[0]);
		exit(0);
    } else {      //recebimento dos parametros da função
    	qtdThread = atoi(argv[1]);
		qtdProc = atoi(argv[2]);
        tamMax = atoi(argv[3]);
	}

    threads = malloc(sizeof(pthread_t) * qtdThread); //cria um array de threads

    comeco = clock();

    for (int i = 0; i < qtdThread; i++){
        srand(time(&t)+i); //para uma pool mais aleatoria
        pthread_create(&threads[i], NULL, randNum, NULL); //para cada thread criada, é gerado um numero aleatorio
    }

    for (int i = 0; i < qtdThread; i++){
        pthread_join(threads[i], (void*)&resThread); //os valores aleatorios sao recebidos e somados
        totalThread += resThread;
    }

    fim = clock();
    tempoTot += (double)(fim - comeco) / CLOCKS_PER_SEC;
    
    printf("numero de threads geradas: %d(%fs)\n", qtdThread, tempoTot); 
    
    //////////////////////////////////////////////////////////////////
    //começo da seção de processos

    pids = (int*) malloc(sizeof(int) * qtdProc); //cria um array de processos

    comeco = clock();

    for (int i = 0; i < qtdProc; i++){ //para cada processo criado, é gerado um numero aleatorio
        if (getpid() == pidOrig){
            pids[i] = fork();
            if (getpid() != pidOrig){
                srand(getpid()+i); //para uma pool mais aleatoria
                resProc = (long)randNum();
                exit(resProc); //os processos filhos retornam o numero aleatorio gerado
                break;
            }else{
                continue;
            }
        }
    }

    fim = clock();
    tempoTot += (double)(fim - comeco) / CLOCKS_PER_SEC;

    printf("Numero de processos gerados: %d(%fs)\n", qtdProc, tempoTot);

    if (getpid() == pidOrig){
        int aux = 0;
        
        for(int i = 0; i < qtdProc; i++){ //para cada processo filho obtem o valor de saida(numero aleatorio) e soma no total
            waitpid(pids[i], &aux, 0); 
            totalProc += WEXITSTATUS(aux); 
        }
	}
    
    printf("Media dos valores gerados pelas threads: %.2f\n", (float)totalThread/qtdThread); //mostra as medias dos valores criados pelas threads e pelos processos
    printf("Media dos valores gerados pelos processos %.2f\n", (float)totalProc/qtdProc);

    return 0;
}