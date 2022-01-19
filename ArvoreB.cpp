
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
    if(no != nullptr) {
        if(!no->isFolha()) {
            for(int i = 0; i < no->getN(); i++) {
                destrutorAux(no->filhos[i]);
                delete no->filhos[i];
            }
        }
    }
}

// recupera a raiz da ArvoreB
NoB *ArvoreB::getRaiz(){
    return this->raiz;
}

// seta a raiz da ArvoreB
void ArvoreB::setRaiz(NoB *raiz){
    this->raiz = raiz;
}

// recupera o grau da ArvoreB
int ArvoreB::getGrau() {
    return this->grau;
}

// seta o grau da ArvoreB
void ArvoreB::setGrau(int grau){
    this->grau = grau;
}

void ArvoreB::percorreNos() {
    // se a ArvoreB não estiver vazia, percorra seus nós a partir da raiz
    if (raiz != nullptr)               
        raiz->percorreNos();
}

// busca um determinado nó na árvore a partir do id de um review
NoB* ArvoreB::buscaNo(string indice, int *comparacoes) {  
    
    if(this->raiz == nullptr)
        return nullptr;
    else 
        return this->raiz->buscaNo(indice, comparacoes);
}

// insere um novo nó na arvore, passando seu id e sua localização no arquivo binário
void ArvoreB::insereNoArvore(string k, int localizacao, int *comparacoes) {
    // instanciando um novo nó do tipó InfoArvore(struct)
    InfoArvoreB *info = new InfoArvoreB();     
    info->id = k;
    info->localizacao = localizacao;

    // se a raiz for nula, defina o novo nó como sendo raiz da ArvoreB
    if (raiz == nullptr) {                     

        raiz = new NoB(this->grau, true, nfilhos);
        raiz->chaves[0] = info;
        raiz->n = 1;
    }
    else
    {
        if (raiz->getN() == nfilhos) {              // verifica se a raiz atingiu o numero máximo de filhos

            NoB *s = new NoB(grau, false, nfilhos); // instanciando um novo nó que será a nova raiz da arvore
            s->filhos[0] = raiz;                    // a então raiz da árvore passa a ter a antigo como filha
            s->particionaNoFilho(0, raiz);          // particionanod a antiga raiz

            // a então raiz da Arvore agora precisa ver qual dos filhos terá a nova chave
            int i = 0;
            if (s->getChaves()[0]->id < k)
                (*comparacoes)++;   // added
                i++;
            s->getFilhos()[i]->insereNoComEspaco(k, localizacao, comparacoes);

            // define s como nova raiz
            raiz = s;
        }
        else // se a raiz não estiver cheia, inserir o novo nó a partir nela
            raiz->insereNoComEspaco(k, localizacao, comparacoes);
    }
}


