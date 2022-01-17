
#include "ArvoreB.h"
#include "NoB.h"
#include <iostream>

using namespace std;

ArvoreB::ArvoreB(int grau, int nfilhos) {
    this->raiz = nullptr;
    this->grau = grau;
    this->nfilhos = nfilhos;
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

    InfoArvoreB *info = new InfoArvoreB();
    info->id = k;
    info->localizacao = localizacao;
    if (raiz == nullptr) {

        raiz = new NoB(this->grau, true, nfilhos);
        raiz->chaves[0] = info;
        //string *vetAux = raiz->getChaves();
        //vetAux[0] = k;
        //raiz->setChaves(vetAux);
        //raiz->setLocalizacao(localizacao);
        //raiz->setN(1);
        raiz->n = 1;
    }
    else
    {
        if (raiz->getN() == nfilhos) {

            NoB *s = new NoB(grau, false, nfilhos);

            s->filhos[0] = raiz;

            //NoB **vetAux2 = raiz->getFilhos();
            //vetAux2[0] = raiz;
            //raiz->setFilhos(vetAux2);

            s->particionaNoFilho(0, raiz);

            int i = 0;
            if (s->getChaves()[0]->id < k)
                i++;
            s->getFilhos()[i]->insereNoComEspaco(k, localizacao);

            raiz = s;
        }
        else 
            raiz->insereNoComEspaco(k, localizacao);
    }
}


