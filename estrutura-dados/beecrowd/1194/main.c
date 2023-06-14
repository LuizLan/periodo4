#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000

typedef struct noArv{

	char letra;
	struct noArv *direita;
	struct noArv *esquerda;

} noArv;

noArv* novoNo(char letra);
void mostrarPos(noArv *arvore);
int src(char *str, int inicio, int fim, char letra);
noArv* arvore(char *infixa, char *prefixa, int inInicio, int inFim);

short indice;

void main (){

	short qntd;
	short qtsNodes, i;
	char prefixa[MAXSIZE], infixa[MAXSIZE];

	scanf("%hu", &qntd);

	while (qntd--){
		scanf("%hu %s %s%*c", &qtsNodes, prefixa, infixa);
		indice = 0;
		noArv *raiz = arvore(infixa, prefixa, 0, qtsNodes - 1);
		mostrarPos(raiz);
		printf("\n");

	}
}

noArv* novoNo(char letra)
{

	noArv *no = (noArv *) malloc(sizeof(noArv));
	no->letra = letra;
	no->esquerda = no->direita = NULL;

	return no;
}

int src(char *str, int inicio, int fim, char letra)
{

	short i;
	for (i = inicio; i <= fim; ++i)
		if (str[i] == letra)
			return i;

	return -1;

}

noArv* arvore(char *infixa, char *prefixa, int inInicio, int inFim)
{

	int infixaIndice;

	if (inInicio > inFim)
		return NULL;

	noArv *no = novoNo(prefixa[indice++]);
	if (inInicio == inFim)
		return no;

	infixaIndice = src(infixa, inInicio, inFim, no->letra);
	no->esquerda = arvore(infixa, prefixa, inInicio, infixaIndice - 1);
	no->direita = arvore(infixa, prefixa, infixaIndice + 1, inFim);

	return no;
}

void mostrarPos(noArv *no)
{

	if (no == NULL)
		return;

	mostrarPos(no->esquerda);
	mostrarPos(no->direita);
	printf("%c", no->letra);

}