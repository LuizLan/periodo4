#include <stdio.h>

int minimos[100000];

int main(){
    char operacao[4];
    int qntd, diversao, minimo, i;

    i = -1;

    scanf("%d\n", &qntd);
    for(int i = 0; i < qntd; ++i){
    	scanf("%s", &operacao);

        if(!memcmp(operacao, "PUSH", 4)){
        	scanf("%d\n", &diversao);

            if(i == -1){
                minimo = diversao;
            }else{
                minimo = (minimos[i] < diversao ? minimos[i] : diversao);
            }

            minimos[++i] = minimo;
        }else if(!memcmp(operacao, "POP", 3)){
            if(i == -1){
            	printf("EMPTY\n");
            }else{
                --i;
            }
        }else{
            if(i == -1){
            	printf("EMPTY\n");
            }else{
            	printf("%d\n", minimos[i]);
            }
        }
    }

    return 0;
}