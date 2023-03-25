#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define QTD_THREADS 5

void *funcao_thread(void *args)
{
    long index = (long)args;
    int count = 0;

    while (count < 50)
    {
        printf("[t]sou a thread %ld (%d)\n", index, count);
        count++;
        usleep(100);
    }

    return (void *)100 + index;

    /*
    int* var_local = (int*) args;
    printf("Sou a thread, meu PID eh: %d, o PID do meu processo pai eh: %d\n", getpid(), getppid());
    printf("var_local: %d\n", *var_local);
    printf("var_global: %d\n", var_global);
    *var_local = 10;
    var_global = 10;
    printf("var_local: %d\n", *var_local);
    printf("var_global: %d\n", var_global);
    return NULL;
    */
}

int main()
{
    pthread_t threads[QTD_THREADS];
    int thread_ret_value[QTD_THREADS];

    printf("[m] programa iniciado\n");

    for (long i = 0; i < QTD_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, funcao_thread, (void *)i);
    }

    for (int i2 = 0; i2 < QTD_THREADS; i2++)
    {
        pthread_join(threads[i2], (void *)&thread_ret_value[i2]);
        printf("[m]thread %d retornou: %d\n", i2, thread_ret_value[i2]);
    }

    return 0;
}