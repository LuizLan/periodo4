#pragma once

#include <iostream>
#include <mutex>
#include <unistd.h>

using namespace std;

class Lebres{

private:
    int indice;
    int puloMax;

public:
    Lebres();
    Lebres(int i, int d);
    virtual ~Lebres();

    void correr(int tamanhoPista);
    void setIndice(int i);
    void setPuloMax(int d);

protected:


};