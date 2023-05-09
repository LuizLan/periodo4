#include <iostream>
#include <stack>

using namespace std;

int main(){
    int i, tamanho;
    string input;
    stack<char> parenteses;

    while(cin >> input){
        while(!parenteses.empty()){
            parenteses.pop();
        }
        tamanho = input.length();

        for(i = 0; i < tamanho; ++i){
            if(input[i] == '('){
                parenteses.push('(');
            }else if(input[i] == ')'){
                if(parenteses.empty())  
                    break;
                else                
                    parenteses.pop();
            }
        }

        if(i == tamanho && parenteses.empty())  
            cout << "correct" << endl;
        else                           
            cout << "incorrect" << endl;
    }

    return 0;
}