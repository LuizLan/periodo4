#include <iostream>
#include "LSE.h"

using namespace std;

int main(){

    LSE lista;
    int tamanho, consultas, ocorrencia, procurado;

    cout << "Insira o tamanho do vetor e o numero de consultas\n";
    cin >> tamanho;
    cin >> consultas;

    for (int i = 0; i < tamanho; i++)
    {
        int valor;
        cout << "Insira o valor do vetor na posicao " << i << endl;
        cin >> valor;
        lista.insere(i+1, valor);
    }
    for (int i = 0; i < consultas; i++)
    {
        cout << "numero da ocorrencia: ";
        cin >> ocorrencia;
        cout << "numero a ser procurado: ";
        cin >> procurado;

        cout << lista.posicao(procurado, ocorrencia) << endl;
    }
    
    return 0;
}