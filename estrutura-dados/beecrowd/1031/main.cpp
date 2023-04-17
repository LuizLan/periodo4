#include<iostream>
#include<vector>
#include<unistd.h>
#include<algorithm>

using namespace std;

int acheM(int N){
    
    vector<int> valores;
    vector<int> antigos;
    
    int salto=0, valor=1;

    for (int i = 1; i <= N; i++){
        valores.push_back(i);
    }

    antigos.push_back(1);

    while(antigos.at(antigos.size()-1) != 13){
        salto++;
        valor = 1;
        do{
            for (int k = 0; k < salto; k++){
                valor++;
                if(valor > valores.size()){
                    valor -= valores.size();
                }
                while(find(antigos.begin(), antigos.end(), valor) != antigos.end()){
                    valor++;
                    if(valor > valores.size()){
                    valor -= valores.size();
                    }
                }
            }
            antigos.push_back(valor);
        } while (antigos.size() < valores.size());
        if (antigos.at(antigos.size()-1) == 13){
        break;   
        }
        antigos.clear();
        antigos.push_back(1);
    }

    return salto;
}

int main(){

    int n, m;

    scanf("%d", &n);

    while (n!=0){
        m = acheM(n);
        printf("%d\n", m);

        scanf("%d", &n);
    }

    return 0;
}