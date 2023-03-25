#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){

    int x;

    x = fork();

    if(x==0){
        printf("sou o processo filho, meu PId eh: %d, o processo do meu processo pai eh %d\n", getpid(), getppid());  
        
        printf("Digite um numero: ");
        scanf("%d", &x);
        printf("O numero digitado foi: %d\n", x);

    }
    else if (x>0){

        int wait_return;

        printf("sou o processo pai, meu PId eh: %d\n", getpid());
        printf("Aguardando clonado\n");
        wait(&wait_return);
        printf("Clonado finalizado\n"); 
    }else if (x<0){

        printf("erro na criacao do processo filho\n");
        return -1;
    }
    

    return 0;
}