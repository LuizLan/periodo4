#include "Listafa.h"
#include <iostream>

Lista::Lista()
{
    qntd = 0;
    
}

Lista::~Lista()
{
}

bool Lista::vazia()
{
    if (qntd == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


int Lista::tamanho()
{
    return qntd; // retorna o tamanho da lista
}

bool Lista::cheia()
{
    if (qntd == 100000)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Lista::alterar(int pos, int valor)
{
    if (pos - 1 < 0 || pos >= qntd)
    {
        return false; // verifica se a posicao eh valida
    }
    else
    {
        lista[pos - 1] = valor; // altera o valor na posicao desejada
        return true;
    }
}

bool Lista::inserir(int pos, int valor)
{
    if (vazia() && pos != 1)
    {
        printf("lista vazia, insira na posicao 1\n");
        return false; // checa se eh possivel adicionar um valor na lista e se a posicao eh valida
    }
    else if (cheia() || pos - 1 < 0)
    {
        printf("lista cheia ou posicao invalida\n");
        return false;
    }
    else
    {
    // [0][1][2][3][4] valor
    // {1}{2}{3}{4}{5} posicao
    //        i
    //        p
    //           q
        for (int i = qntd; i > pos; i--)
        {
            lista[i] = lista[i-1]; // desloca os valores Listaa a direita Listaa que o valor possa ser adicionado
        }

        lista[pos-1] = valor; // adiciona o valor na posicao desejada
        qntd++;                 // aumenta a quantidade de valores na lista
        return true;
    }
}

bool Lista::remover(int pos)
{
    if (pos < 0 || pos >= qntd)
    {
        return false; // verifica se a posicao eh valida
    }
    else
    {

        for (int i = pos; i < qntd; i++)
        {
            lista[i - 1] = lista[i]; // move a lista para a esquerda
            qntd--;                  // diminui a quantidade de valores na lista
        }

        return true;
    }
}

bool Lista::esvaziar()
{
    qntd = 0; // zera a quantidade de valores na lista
    return true;
}

int Lista::getPosicao(int pos)
{
    if (pos - 1 < 0 || pos > qntd)
    {
        return false; // verifica se a posicao eh valida
    }
    else
    {
        return lista[pos-1]; // retorna o valor na posicao desejada
    }
}

int Lista::getValor(int valor, int ocorrencia)
{
    int ocorr = 0;

    for (int i = 0; i < qntd - 1; i++)
    {
        if (lista[i] == valor)
        {
            ocorr++; 
        }
        if(ocorr == ocorrencia){
            return i+1;
        }
    }
    return 0;
}