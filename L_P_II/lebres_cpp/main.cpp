#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include "Lebres.h"

using namespace std;

#define QTD_PARAM 4
#define PULO_MAX 10

mutex m;

int main(int argc, char const *argv[]){

    time_t t;
    int *pids;
    int qntdLebres, tamPista;
    char concorrencia;
    
    if (argc != QTD_PARAM) {

		printf("use: %s [t/p] <quantidade> <tamPista>\n",
		argv[0]);
		exit(0);

	} else {

		if((argv[1][0] != 't') && (argv[1][0] != 'p')){
			printf("use: %s [t/p] <quantidade> <tamPista>\n",
                        argv[0]);
        	        exit(0);
		}

		concorrencia = argv[1][0];
		qntdLebres = atoi(argv[2]);
		tamPista = atoi(argv[3]);
	}

    srand(time(&t));

    if(concorrencia =='t'){
        thread* t[qntdLebres];
        
        cout << "Executando corrida com threads!\n";
        cout << "Quantidade de lebres: " << qntdLebres << endl;
        cout << "Tamanho da pista: " << tamPista << endl;
        
        for (int i = 0; i < qntdLebres; i++){
            t[i] = new thread(&Lebres::correr, new Lebres(i+1, (rand()%PULO_MAX)+1), tamPista);
        }

        for (int i = 0; i < qntdLebres; i++){
            t[i]->join();
        }
    }else if(concorrencia == 'p'){

        int pid_original = getpid();

        cout << "Executando corrida com processos!\n";
        cout << "Quantidade de lebres: " << qntdLebres << endl;
        cout << "Tamanho da pista: " << tamPista << endl;
        vector <Lebres> lebres(qntdLebres);

        for (int i = 0; i < qntdLebres; i++){
            lebres[i].setIndice(i+1);
            lebres[i].setPuloMax((rand()%PULO_MAX)+1);
        }

        vector <int> pids(qntdLebres);

        for (int i = 0; i < qntdLebres; i++){
            if (getpid() == pid_original){
                pids[i] = fork();
                if (getpid() != pid_original){
                    lebres[i].correr(tamPista);
                    break;
                }else{
                    continue;
                }   
            }
        }
        if (getpid()==pid_original){
            int retval = 0;
            wait(&retval);
            cout << "Saindo...\n";
            for (int i = 0; i < qntdLebres; i++){
                kill(pids[i], SIGINT);
            }
            exit(0);
        }
    }

    return 0;
}
