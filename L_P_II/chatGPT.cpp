#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;

// Função que a lebre executa
void correr(int id, double max_salto, double distancia_pista, bool* acabou) {
    double distancia_percorrida = 0;
    srand(time(NULL) + id); // Seed para geração de números aleatórios (com base no id da lebre)

    while (distancia_percorrida < distancia_pista) {
        double salto = rand() % (int)max_salto + 1; // Gera um número aleatório entre 1 e o valor máximo do salto da lebre
        distancia_percorrida += salto / 100; // Converte para metros
        cout << "lebre " << id << " saltou " << salto << "cm (total: " << distancia_percorrida << "m)" << endl;
        sleep(1); // Espera 1 segundo antes do próximo salto
    }

    if (!*acabou) {
        *acabou = true;
        cout << "lebre " << id << " venceu!" << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) { // Verifica se foram passados os argumentos corretos
        cout << "Uso: " << argv[0] << " -p/-t <n_lebres> <distancia_pista>" << endl;
        return 1;
    }

    bool use_processos = false;
    bool use_threads = false;

    if (strcmp(argv[1], "-p") == 0) {
        use_processos = true;
    } else if (strcmp(argv[1], "-t") == 0) {
        use_threads = true;
    } else {
        cout << "Opção inválida. Use -p para processos ou -t para threads." << endl;
        return 1;
    }

    int n_lebres = atoi(argv[2]);
    double distancia_pista = atof(argv[3]);

    if (n_lebres <= 0 || distancia_pista <= 0) { // Verifica se os valores dos argumentos são válidos
        cout << "Valores inválidos." << endl;
        return 1;
    }

    bool acabou = false;
    thread* threads = new thread[n_lebres];
    pid_t* pids = new pid_t[n_lebres];

    for (int i = 0; i < n_lebres; i++) {
        if (use_threads) {
            threads[i] = thread(correr, i, distancia_pista / 3, distancia_pista, &acabou);
        } else if (use_processos) {
            pids[i] = fork();
            if (pids[i] == 0) {
                correr(i, distancia_pista / 3, distancia_pista, &acabou);
                exit(0);
            }
        }
    }

    if (use_threads) {
        for (int i = 0; i < n_lebres; i++) {
            threads[i].join();
        }
    } else if (use_processos) {
        for (int i = 0; i < n_lebres; i++) {
            waitpid(pids[i], NULL, 0);
        }
    }

    delete[] threads;

    return 0;
}