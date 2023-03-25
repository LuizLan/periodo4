#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define EXEC_PATH "/home/luiz/Cod/periodo4/L_P_II/loop"

int main()
{
    int fork_return;

    fork_return = fork();

    if (fork_return < 0)
    {
        printf("Erro na criacao do processo filho\n");
    }
    else if (fork_return == 0)
    {
        // processo filho
        char *args[] = {"loop", "1000", NULL};
        printf("irei executar o programa loop\n");
        int exec_return = execv(EXEC_PATH, args);
        printf("[c]depois do exec: %d\n", exec_return);
    }
    else
    {
        // processo original
        int ret_val;
        waitpid(fork_return, &ret_val, 0);
        printf("[o] clone finalizado\n");
    }

    return 0;
}