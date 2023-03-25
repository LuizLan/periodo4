#include<stdio.h>

int main(){

    int x, i, qntd, pid0;

    pid0 == getpid();

    printf("Digite o numero de processos que devem ser criados: ");
    scanf("%d", &qntd);

    printf("criando %d processos filhos\n", qntd);

    for (i = 0; i < qntd; i++){
        if (getpid() == pid0){
            fork();
        }
        if (getpid() != pid0){
            sleep(15);
        }   
    }

    return 0;
}