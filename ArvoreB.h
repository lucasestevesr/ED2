#ifndef ED2_ARVOREB_H
#define ED2_ARVOREB_H
#include <iostream>
#include "NoB.h"

class ArvoreB
{
    private:
        NoB *raiz; // ponteiro para o nó raiz
        int grau;  // grau minimo da arvore
        int nfilhos;
        void destrutorAux(NoB* no);

    public:
        ArvoreB(int grau, int nfilhos);
        ~ArvoreB();
        NoB *getRaiz();
        void setRaiz(NoB *raiz);
        int getGrau();
        void setGrau(int grau);
        void percorreNos();
        NoB* buscaNo(string k, int *comparacoes_busca);
        void insereNoArvore(string k, int localizacao, int *comparacoes);
};


#endif