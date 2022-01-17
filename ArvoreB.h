#ifndef ED2_ARVOREB_H
#define ED2_ARVOREB_H
#include <iostream>
#include "NoB.h"

class ArvoreB
{
private:

    NoB *raiz; // ponteiro para o nó raiz
    int grau;  // grau minimo da arvore

    void destrutorAux(NoB* no);

public:

    ArvoreB(int grau);

    ~ArvoreB();

    NoB *getRaiz();

    void setRaiz(NoB *raiz);

    int getGrau();

    void setGrau(int grau);

    void percorreNos();
    NoB* buscaNo(string k);
    void insereNoArvore(string k, int localizacao);
};


#endif