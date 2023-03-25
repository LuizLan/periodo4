/*
 * No.cpp
 *
 *  Created on: 20 de out. de 2022
 *      Author: tiagomaritan
 */

#include "No.h"
#include <stdlib.h>

No::No() {
	setAnt(NULL);
	setProx(NULL);
}

No::~No() {
}

int No::getConteudo() {
	return conteudo;
}

void No::setConteudo(int conteudo) {
	this->conteudo = conteudo;
}

No *No::getProx() {
	return prox;
}

void No::setProx(No *prox) {
	this->prox = prox;
}

No *No::getAnt() {
	return ant;
}

void No::setAnt(No *ant) {
	this->ant = ant;
}


