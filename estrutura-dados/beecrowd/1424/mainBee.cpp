#include <iostream>

using namespace std;

class No
{

private:
	int conteudo;
	No *prox;

public:
	No();
	virtual ~No();

	int getConteudo();
	No *getProx();

	void setConteudo(int conteudo);
	void setProx(No *prox);
};

No::No()
{
	setConteudo(0);
	setProx(NULL);
}

No::~No()
{
}

int No::getConteudo()
{
	return conteudo;
}

void No::setConteudo(int conteudo)
{
	this->conteudo = conteudo;
}

No *No::getProx()
{
	return prox;
}

void No::setProx(No *prox)
{
	this->prox = prox;
}

class LSE
{

private:
	No *cabeca;
	int nElementos;

	bool insereInicioLista(int valor);
	bool insereMeioLista(int pos, int valor);

	int removeInicioLista();
	int removeNaLista(int pos);

public:
	LSE();
	virtual ~LSE();

	bool vazia();
	int tamanho();
	int elemento(int pos);
	int posicao(int valor);
	int posicao(int valor, int ocorrencia);
	bool insere(int pos, int valor);
	int remove(int pos);
};

LSE::LSE()
{
	cabeca = NULL;
	nElementos = 0;
}

LSE::~LSE()
{
}

/** Verifica se a Lista está vazia */
bool LSE::vazia()
{
	return (nElementos == 0);
}

/**Obtém o tamanho da Lista*/
int LSE::tamanho()
{
	// return nElementos;

	No *aux = cabeca;
	int cont = 0;
	while (aux != NULL)
	{
		aux = aux->getProx();
		cont++;
	}
	return cont;
}

/** Obtém o i-ésimo elemento de uma lista
	  Retorna o valor encontrado. */
int LSE::elemento(int pos)
{
	if (vazia())
		return -1; // Consulta falhou

	if ((pos < 1) || (pos > tamanho()))
		return -1; // Posicao invalida

	No *aux = cabeca;

	// Percorre a lista do 1o elemento até pos
	for (int i = 1; i < pos; i++)
	{
		// modifica "aux" para apontar para o proximo elemento da lista
		aux = aux->getProx();
	}

	return aux->getConteudo();
}

/**Retorna a posição de um elemento pesquisado.
	Retorna -1 caso não seja encontrado */
int LSE::posicao(int dado)
{
	/* Lista vazia */
	if (vazia())
		return -1;

	/* Percorre a lista do inicio ao fim até encontrar o elemento*/
	No *aux = cabeca;
	int cont = 1;
	while (aux != NULL)
	{
		// Se encontrar o elemento, retorna sua posicao n;
		if (aux->getConteudo() == dado)
		{
			return cont;
		}
		// modifica "aux" para apontar para o proximo elemento da lista
		aux = aux->getProx();
		cont++;
	}

	return -1;
}

int LSE::posicao(int dado, int ocorrencia)
{
	if (vazia())
		return -1;

	/* Percorre a lista do inicio ao fim até encontrar o elemento*/
	No *aux = cabeca;
	int cont = 1, ocorr = 0;
	while (aux != NULL)
	{
		// Se encontrar o elemento, retorna sua posicao n;
		if (aux->getConteudo() == dado)
		{
			ocorr++;
			if (ocorr == ocorrencia)
			{
				return cont;
			}
		}
		// modifica "aux" para apontar para o proximo elemento da lista
		aux = aux->getProx();
		cont++;
	}
	return 0;
}

/** Insere nó em lista vazia */
bool LSE::insereInicioLista(int valor)
{
	// Aloca memoria para novo no
	No *novoNo = new No();

	// Insere novo elemento na cabeca da lista
	novoNo->setConteudo(valor);

	novoNo->setProx(cabeca);
	cabeca = novoNo;
	nElementos++;
	return true;
}

/** Insere nó no meio da lista */
bool LSE::insereMeioLista(int pos, int valor)
{

	// Aloca memoria para novo no
	No *novoNo = new No();
	novoNo->setConteudo(valor);

	// Localiza a pos. ANTERIOR onde será inserido o novo nó
	No *aux = cabeca;
	for (int i = 1; i < pos - 1; i++)
	{
		// modifica "aux" para apontar para o proximo elemento da lista
		aux = aux->getProx();
	}

	// Insere novo elemento apos aux
	novoNo->setProx(aux->getProx());
	aux->setProx(novoNo);

	nElementos++;
	return true;
}

/**Insere um elemento em uma determinada posição
		Retorna true se conseguir inserir e
		false caso contrario */
bool LSE::insere(int pos, int valor)
{
	if ((vazia()) && (pos != 1))
		return false; /* lista vazia mas posicao inv*/

	if ((pos <= 0) || pos > (nElementos + 1))
		return false; // posicao invalida

	/* inserção no início da lista (ou lista vazia)*/
	if (pos == 1)
		return insereInicioLista(valor);
	else
		return insereMeioLista(pos, valor);
}

/** Remove elemento do início da lista */
int LSE::removeInicioLista()
{

	No *p = cabeca;

	// Dado recebe o dado removido
	int valorRemovido = p->getConteudo();

	// Retira o 1o elemento da lista (p)
	cabeca = p->getProx();
	nElementos--;

	// Remove o objeto apontado por p
	delete p;

	return valorRemovido;
}

/** Remove elemento no meio da lista */
int LSE::removeNaLista(int pos)
{
	// Localiza os nó a ser removido (atual) e o seu
	// antecessor (antecessor)
	No *antecessor = cabeca;
	for (int i = 1; i < pos - 1; i++)
	{
		antecessor = antecessor->getProx();
	}

	No *atual = antecessor->getProx();

	// Guarda o valor a ser removido
	int valorRemovido = atual->getConteudo();

	// Faz o campo prox de antecessor apontar pro prox de atual
	// No aux = atual.getProx();
	// antecessor.setProx(aux);
	antecessor->setProx(atual->getProx());

	// Decrementa o numero de elementos
	nElementos--;

	// Libera a area de memoria do no atual
	delete atual;

	return valorRemovido;
}

/**Remove um elemento de uma determinada posição
	 Retorna o valor a ser removido.
	-1 se a posição for inválida ou a lista estiver vazia*/
int LSE::remove(int pos)
{
	if (vazia())
		return -1; // Lista vazia

	if ((pos <= 0) || (pos > nElementos))
		return -1; // Posicao invalida

	if (pos == 1)
		return removeInicioLista();
	else
		return removeNaLista(pos);
}

int main()
{

	LSE lista;
	long int tamanho, consultas, ocorrencia, procurado;

	while (!cin.eof())
	{
	// cout << "Insira o tamanho do vetor e o numero de consultas\n";
		cin >> tamanho;
		cin >> consultas;

		for (int i = 0; i < tamanho; i++)
		{
			int valor;
			// cout << "Insira o valor do vetor na posicao " << i << endl;
			cin >> valor;
			lista.insere(i + 1, valor);
		}

		for (int i = 0; i < consultas; i++)
		{
			// cout << "numero da ocorrencia: ";
			cin >> ocorrencia;
			// cout << "numero a ser procurado: ";
			cin >> procurado;

			cout << lista.posicao(procurado, ocorrencia) << endl;
		}
	}
	return 0;
}