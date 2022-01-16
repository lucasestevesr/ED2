#ifndef ED2_ARVOREB_H
#define ED2_ARVOREB_H
#include <iostream>
#include "NoB.h"

class ArvoreB
{
    NoB *raiz; // ponteiro para o nó raiz
    int grau;  // grau minimo da arvore
public:

    ArvoreB(int _grau);    
    ~ArvoreB();
    void percorreNos();
    NoB* buscaNo(int k);
    void insereNoArvore(int k);
};


#endif