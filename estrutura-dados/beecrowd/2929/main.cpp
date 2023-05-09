#include <iostream>
#include <stack>

using namespace std;

int main(){
    int qntd, diversao;
    string operacao;
    stack<int> minimos;

    cin >> qntd;
    for(int i = 0; i < qntd; ++i){
        cin >> operacao;

        if(operacao == "PUSH"){
            cin >> diversao;

            if(minimos.empty()){
                minimos.push(diversao);
            }else{
            	minimos.push(min(minimos.top(), diversao));
            }
        }else if(operacao == "POP"){
            if(minimos.empty()){
                cout << "EMPTY" << endl;
            }else{
                minimos.pop();
            }
        }else{
            if(minimos.empty()){
                cout << "EMPTY" << endl;
            }else{
                cout << minimos.top() << endl;
            }
        }
    }

    return 0;
}