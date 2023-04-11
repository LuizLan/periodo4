#include "Lebres.h"

Lebres::Lebres(){

}

Lebres::Lebres(int i, int d){
    indice = i;
    puloMax = d;

}

Lebres::~Lebres(){

}

void Lebres::correr(int tamanhoPista){
    int posicao = 0;
    int puloAtual = 0;

    do{
        puloAtual = rand() % puloMax + 1;
        posicao += puloAtual;
        sleep(1);
        cout <<"["<<indice <<"]"<<" pulou "<<puloAtual<<"m"<<"("<<posicao<<")\n";
        if (posicao > tamanhoPista){
            cout << "Lebre " << indice << " ganhou\n";
            exit(0);
        }

    }while(posicao < tamanhoPista);
}

void Lebres::setIndice(int i){
    indice = i;
}
void Lebres::setPuloMax(int d){
    puloMax = d;
}