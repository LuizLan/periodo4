#include <iostream>
#include <stack>
#include <queue>

using namespace std;

int main()
{
    bool pilhaBol, filaBol, filaPrioBol;
    queue<int> fila;
    stack<int> pilha;
    int n, operacao, numero;
    priority_queue<int> filaPrioridade;

    while (cin >> n)
    {
        while (!pilha.empty())
            pilha.pop();
        while (!fila.empty())
            fila.pop();
        while (!filaPrioridade.empty())
            filaPrioridade.pop();

        pilhaBol = true, filaBol = true, filaPrioBol = true;
        for (int i = 0; i < n; ++i)
        {
            cin >> operacao >> numero;

            if (operacao == 1)
            {
                if (pilhaBol)
                    pilha.push(numero);
                if (filaBol)
                    fila.push(numero);
                if (filaPrioBol)
                    filaPrioridade.push(numero);
            }
            else
            {
                if (pilhaBol)
                {
                    if (pilha.empty() || pilha.top() != numero)
                        pilhaBol = false;
                    else
                        pilha.pop();
                }

                if (filaBol)
                {
                    if (fila.empty() || fila.front() != numero)
                        filaBol = false;
                    else
                        fila.pop();
                }

                if (filaPrioBol)
                {
                    if (filaPrioridade.empty() || filaPrioridade.top() != numero)
                        filaPrioBol = false;
                    else
                        filaPrioridade.pop();
                }
            }
        }

        if (pilhaBol && !filaBol && !filaPrioBol)
            cout << "stack" << endl;
        else if (!pilhaBol && filaBol && !filaPrioBol)
            cout << "queue" << endl;
        else if (!pilhaBol && !filaBol && filaPrioBol)
            cout << "priority queue" << endl;
        else if (!pilhaBol && !filaBol && !filaPrioBol)
            cout << "impossible" << endl;
        else
            cout << "not sure" << endl;
    }

    return 0;
}