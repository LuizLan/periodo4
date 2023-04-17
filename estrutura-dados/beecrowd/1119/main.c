#include <stdio.h>
#include <stdlib.h>

typedef struct vitima{

    int id;
    struct vitima *ant;
    struct vitima *prox;
} vitima_t;

vitima_t *fill(int);
vitima_t *delete(vitima_t *, vitima_t *);
int count(vitima_t *);
vitima_t *traverse(vitima_t *, int, int);

int main(int argc, char **argv){

    int n, k, m, i;
    vitima_t *list, *K, *M, *auxK, *auxM;

    while (scanf("%d %d %d", &n, &k, &m), n){

        list = fill(n);
        K = list;
        M = list->ant;

        while (count(list) > 2){

            K = traverse(K, k, 0x0);
            M = traverse(M, m, 0x1);

            if (K->prox == M)
                auxK = M->prox;
            else
                auxK = K->prox;

            if (M->ant == K)
                auxM = K->ant;
            else
                auxM = M->ant;

            if (K == M){
                printf("%3d,", M->id);
                list = delete (list, K);
            }
            else{
                printf("%3d%3d,", K->id, M->id);
                list = delete (list, M);
                list = delete (list, K);
            }

            K = auxK;
            M = auxM;
        }

        if (count(list) == 2){
            K = traverse(K, k, 0x0);
            M = traverse(M, m, 0x1);

            if (K == M)
                printf("%3d,%3d\n", K->id, K->prox->id);
            else
                printf("%3d%3d\n", K->id, K->prox->id);
        }
        else
            printf("%3d\n", list->id);
    }

    return 0;
}

vitima_t *fill(int size){

    vitima_t *no;
    vitima_t *no_ant;
    vitima_t *start = NULL;

    for (int i = 1; i <= size; ++i){

        no = (vitima_t *)malloc(sizeof(vitima_t));
        no->id = i;

        if (start == NULL)
            start = no;
        else{
            no_ant->prox = no;
            no->ant = no_ant;
        }

        no_ant = no;
    }

    start->ant = no;
    no->prox = start;

    return start;
}

vitima_t *delete (vitima_t *list, vitima_t *reg){
    vitima_t *no_ant = reg->ant;
    vitima_t *no_prox = reg->prox;

    if (reg == list){
        list = list->prox;
        no_ant->prox = list;
        list->ant = reg->ant;
    }
    else{
        no_ant->prox = no_prox;
        no_prox->ant = no_ant;
    }

    free(reg);
    return list;
}

int count(vitima_t *list){

    int i;
    vitima_t *no = list;
    for (i = 1; list != no->prox; ++i)
        no = no->prox;

    return i;
}

vitima_t *traverse(vitima_t *list, int n, int direction){

    vitima_t *no = list;
    if (direction == 0)
        while (--n)
            no = no->prox;
    else
        while (--n)
            no = no->ant;

    return no;
}