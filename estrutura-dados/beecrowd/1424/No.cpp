/*
 * No.cpp
 *
 *  Created on: 19 de out. de 2022
 *      Author: Administrador
 */

#include <stdlib.h>
#include "No.h"

No::No() {
	setConteudo(0);
	setProx(NULL);
}

No::~No() {
}


long No::getConteudo() {
	return conteudo;
}

void No::setConteudo(long conteudo) {
 this->conteudo = conteudo;
}

No *No::getProx(){
	return prox;
}

void No::setProx(No *prox) {
	this->prox = prox;
}

