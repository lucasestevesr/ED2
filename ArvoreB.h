#ifndef ED2_ARVOREB_H
#define ED2_ARVOREB_H
#include <iostream>
#include "NoB.h"

class ArvoreB {

    private:
        NoB* raiz;
        int grauArvore;
    public:
        ArvoreB(int grau);
        ~ArvoreB();
        bool vazia();
        void imprime();
        NoB *busca(int val); 
        void percorreArvore(int indiceBusca);
        void insereNo(int indice);
        
};

#endif