#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{

    int pid_O = getpid();
    int retVal, proc_clone[5];

    for (int i = 0; i < 5; i++)
    {
        if (pid_O == getpid())
        {
            retVal = fork();
            if (retVal == 0)
            {
                printf("[c]processo clonado %d\n", i);
                sleep(1);
            }
            else
            {
                proc_clone[i] = retVal;
            }
        }
    }

    if (getpid() == pid_O)
    {
        for (int i = 0; i < 5; i++)
        {
            waitpid(proc_clone[i], NULL, 0);
        }
        printf("[p]processo pai finalizado\n");
    }

    return 0;
}