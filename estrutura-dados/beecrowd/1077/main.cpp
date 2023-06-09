#include <iostream>
#include <cctype>
#include <stack>

using namespace std;

int precedencia(char operador){
    switch(operador){
        case '+':
        case '-':   return 1;
        case '*':
        case '/':   return 2;
    }
}

int main(){
    int qntd;
    string expressao;
    stack<char> pilha;

    cin >> qntd;

    for(int k = 0; k < qntd; ++k){
        
        cin >> expressao;
        
        for(int i = 0; i < expressao.length(); ++i){
            if(isalpha(expressao[i]) || isdigit(expressao[i])){
                cout << expressao[i];
            }else if(expressao[i] == '(' || expressao[i] == '^'){
                pilha.push(expressao[i]);
            }else if(expressao[i] == ')'){
                while(!pilha.empty() && pilha.top() != '('){
                    cout << pilha.top();
                    pilha.pop();
                }
                if(!pilha.empty()){  
                    pilha.pop();
                }
            }else{
                while(!pilha.empty() && pilha.top() != '(' && precedencia(expressao[i]) <= precedencia(pilha.top())){
                    cout << pilha.top();
                    pilha.pop();
                }
                pilha.push(expressao[i]);
            }
        }

        while(!pilha.empty()){
            cout << pilha.top();
            pilha.pop();
        }
        cout << endl;
    }

    return 0;
}