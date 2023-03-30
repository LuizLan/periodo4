#pragma once


class Lista
{

private:
    int qntd;
    int lista[100000];

public:
    Lista();
    virtual ~Lista();

    bool vazia();
    bool cheia();
    int tamanho();
    bool alterar(int pos, int valor);
    bool inserir(int pos, int valor);
    bool remover(int pos);
    bool esvaziar();

    int getPosicao(int pos);
    int getValor(int valor, int ocorrencia);

protected:
};