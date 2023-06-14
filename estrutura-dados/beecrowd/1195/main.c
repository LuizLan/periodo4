#include <stdio.h>
#include <stdlib.h>

typedef struct noArv{

	int numero;
	struct noArv *esquerda;
	struct noArv *direita;

} noArv;

noArv* insere(noArv *, int);
void mostrarPre(noArv *);
void mostrarIn(noArv *);
void mostrarPos(noArv *);
void apagar(noArv *);

void main ()
{

	unsigned short i;
	int numero;

	unsigned short qtdNo;
	unsigned short qtd, caso = 0;

	scanf("%hu", &qtd);

	while (qtd--)
	{

		noArv *arvore = NULL;
		scanf("%hu", &qtdNo);

		for (i = 0; i < qtdNo; i++)
		{

			scanf("%d", &numero);
			arvore = insere(arvore, numero);

		}

		printf("Case %hu:\n", ++caso);
		printf("Pre.:");
		mostrarPre(arvore);
		printf("\n");
		printf("In..:");
		mostrarIn(arvore);
		printf("\n");
		printf("Post:");
		mostrarPos(arvore);
		printf("\n\n");
		apagar(arvore);

	}
}

noArv* insere(noArv *arvore, int numero)
{

	if (!arvore)
	{

		arvore = (noArv *) malloc(sizeof(noArv));
		arvore->numero = numero;
		arvore->esquerda = arvore->direita = NULL;

	}
	else if (arvore->numero > numero)
		arvore->esquerda = insere(arvore->esquerda, numero);

	else
		arvore->direita = insere(arvore->direita, numero);

	return arvore;

}

void mostrarPos(noArv *arvore)
{

	if (arvore)
	{

		mostrarPos(arvore->esquerda);
		mostrarPos(arvore->direita);
		printf(" %d", arvore->numero);

	}

}

void mostrarPre(noArv *arvore)
{

	if (arvore)
	{

		printf(" %d", arvore->numero);
		mostrarPre(arvore->esquerda);
		mostrarPre(arvore->direita);

	}

}
void mostrarIn(noArv *arvore)
{

	if (arvore)
	{

		mostrarIn(arvore->esquerda);
		printf(" %d", arvore->numero);
		mostrarIn(arvore->direita);

	}

}

void apagar(noArv *arvore)
{

	if (arvore)
	{

		apagar(arvore->esquerda);
		apagar(arvore->direita);
		free(arvore);
		arvore = NULL;

	}

}