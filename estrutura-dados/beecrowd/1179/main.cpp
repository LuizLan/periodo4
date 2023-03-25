#include <iostream>
#include "Lista.h"

using namespace std;

int main()
{

    int n, i, qntd = 15;

    Lista par;
    Lista impar;
 
    while (qntd--)
    {
        cout << "Digite um numero: ";
        cin >> n;

        if (n % 2 == 0)
        {
            par.inserir(par.tamanho()+1, n);

            if (par.cheia())
            {
                for (i = 0; i < par.tamanho(); i++)
                {
                    cout << "par[" << i << "] = " << par.getPosicao(i+1) << endl;
                }   
                par.esvaziar();
            }
        }
        else
        {
            impar.inserir(impar.tamanho()+1, n);

            if (impar.cheia())
            {
                for (i = 0; i < impar.tamanho(); i++)
                {
                    cout << "impar[" << i << "] = " << impar.getPosicao(i+1) << endl;
                }   
                impar.esvaziar();
            }
        }
    }

    for (i = 0; i < impar.tamanho(); i++)
    {
        cout << "impar[" << i << "] = " << impar.getPosicao(i+1) << endl;
    }   
    for (i = 0; i < par.tamanho(); i++)
    {
        cout << "par[" << i << "] = " << par.getPosicao(i+1) << endl;
    }

    return 0;
}