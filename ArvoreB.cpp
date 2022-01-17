
#include "ArvoreB.h"
#include "NoB.h"
#include <iostream>

using namespace std;

ArvoreB::ArvoreB(int grau) {
    this->raiz = nullptr;
    this->grau = grau;
}

// Destrutor
ArvoreB::~ArvoreB() {
    ArvoreB::destrutorAux(this->raiz);
}

// Destrutor Auxiliar
void ArvoreB::destrutorAux(NoB *no) {
    // Destrutor auxiliar que vai chamando as subarvores
    // da esquerda e da direita recursivamente
    if(no != nullptr) {
        //ArvoreB::destrutorAux(no->getEsquerdo());
        //ArvoreB::destrutorAux(no->getDireito());
        delete no;
    }
}

NoB *ArvoreB::getRaiz(){
    return this->raiz;
}

void ArvoreB::setRaiz(NoB *raiz){
    this->raiz = raiz;
}

int ArvoreB::getGrau() {
    return this->grau;
}

void ArvoreB::setGrau(int grau){
    this->grau = grau;
}


void ArvoreB::percorreNos() {
    
    if (raiz != nullptr)
        raiz->percorreNos();
}

NoB* ArvoreB::buscaNo(string indice) {
    
    if(this->raiz == nullptr)
        return nullptr;
    else 
        return this->raiz->buscaNo(indice);
}

void ArvoreB::insereNoArvore(string k, int localizacao) {

    if (raiz == nullptr) {

        raiz = new NoB(this->grau, true);

        string *vetAux = raiz->getChaves();
        vetAux[0] = k;
        raiz->setChaves(vetAux);
        //raiz->setLocalizacao(localizacao);
        raiz->setN(1);
    }
    else
    {
        if (raiz->getN() == 2*grau-1) {

            NoB *s = new NoB(grau, false);

            NoB **vetAux2 = raiz->getFilhos();
            vetAux2[0] = raiz;
            raiz->setFilhos(vetAux2);

            s->particionaNoFilho(0, raiz);

            int i = 0;
            if (s->getChaves()[0] < k)
                i++;
            s->getFilhos()[i]->insereNoComEspaco(k);

            raiz = s;
        }
        else 
            raiz->insereNoComEspaco(k);
    }
}


