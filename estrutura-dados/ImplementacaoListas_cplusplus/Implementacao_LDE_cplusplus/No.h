/*
 * No.h
 *
 *  Created on: 20 de out. de 2022
 *      Author: tiagomaritan
 */

#ifndef NO_H_
#define NO_H_

class No {

private:
	int conteudo;
	No *ant;
	No *prox;

public:
	No();
	virtual ~No();

	int getConteudo();
	No *getProx();
	No *getAnt();

	void setConteudo(int conteudo);
	void setProx(No *prox);
	void setAnt(No *ant);

};

#endif /* NO_H_ */
