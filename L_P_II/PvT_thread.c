#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *funcao_thread(void *p)
{
    long index = (long)p;

    printf("Sou a thread %ld\n", index);
    sleep(3);
    printf("Bye\n");
}

int main()
{

    pthread_t threads[5];

    for (long i = 0; i < 5; i++)
    {
        pthread_create(&threads[i], NULL, funcao_thread, (void *)i);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("Bye main\n");

    return 0;
}