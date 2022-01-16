
#include "ArvoreB.h"
#include "NoB.h"
#include <iostream>

using namespace std;

ArvoreB::ArvoreB(int grau) {
    this->raiz = NULL;
    this->grau = grau;
}

ArvoreB::~ArvoreB() { }

void ArvoreB::percorreNos() {
    
    if (raiz != NULL)
        raiz->percorreNos();
}

NoB* ArvoreB::buscaNo(int indice) {
    
    if(this->raiz == NULL) 
        return NULL;
    else 
        return this->raiz->buscaNo(indice);
}


void ArvoreB::insereNoArvore(int k) {   

    if (raiz == NULL) {
        
        raiz = new NoB(this->grau, true);
        raiz->chaves[0] = k;  
        raiz->n = 1;  
    }
    else
    {
        if (raiz->n == 2*grau-1) {

            NoB *s = new NoB(grau, false);
 
            s->filhos[0] = raiz;
 
            s->particionaNoFilho(0, raiz);

            int i = 0;
            if (s->chaves[0] < k)
                i++;
            s->filhos[i]->insereNoComEspaco(k);
 
            raiz = s;
        }
        else 
            raiz->insereNoComEspaco(k);
    }
}