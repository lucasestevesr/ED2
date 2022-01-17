#include <iostream>
#include "NoB.h"

using namespace std;


NoB::NoB(int grau, bool folha, int nfilhos) {

    this->grau = grau;
    this->folha = folha;
    this->chaves = new InfoArvoreB *[2*grau-1];
    this->filhos = new NoB *[2*grau];
    this->n = 0;
    this->nfilhos = nfilhos;
}

NoB::~NoB() {}

// Função que percorre todos os nós pertencentes a um nó específico 

void NoB::percorreNos() {

    int i;
    for (i = 0; i < n; i++) {

        if (!folha)
            filhos[i]->percorreNos();
        cout << " " << chaves[i];
    }
 
    if (!folha)
        filhos[i]->percorreNos();
}
 
// Busca uma chave específica em um determinado nó

NoB *NoB::buscaNo(string k) {

    int i = 0;
    while (i < n && k > chaves[i]->id)
        i++;

    if (chaves[i]->id == k)
        return this;

    if (folha)
        return nullptr;
 
    return filhos[i]->buscaNo(k);
}

// Função que insere um no na subarvore daquele nó desde que o nó tenha espaço para inserir uma nova chave

void NoB::insereNoComEspaco(string k, int localizacao) {

    InfoArvoreB* info = new InfoArvoreB();
    info->id = k;
    info->localizacao = localizacao;
    int i = n-1;

    if (folha) {

        while (i >= 0 && chaves[i]->id > k) {
            chaves[i+1] = chaves[i];
            i--;
        }
        chaves[i+1] = info;
        n = n+1;
    }
    else 
    {
        while (i >= 0 && chaves[i]->id > k)
            i--;
 
        if (filhos[i+1]->n == nfilhos) {
            particionaNoFilho(i+1, filhos[i+1]);
 
            if (chaves[i+1]->id < k)
                i++;
        }
        filhos[i+1]->insereNoComEspaco(k, localizacao);
    }
}
 
// função utilizada para inserir um nó quando o filho de um determinado nó estiver totalmente cheio.
void NoB::particionaNoFilho(int i, NoB *y) {

    NoB *z = new NoB(y->grau, y->folha, y->nfilhos);
    z->n = grau - 1;
 
    for (int j = 0; j < grau-1; j++)
        z->chaves[j] = y->chaves[j+grau];
 
    if (!y->folha) {
        for (int j = 0; j < grau; j++)
            z->filhos[j] = y->filhos[j+grau];
    }

    y->n = grau - 1;

    for (int j = n; j >= i+1; j--)
        filhos[j+1] = filhos[j];
 
    filhos[i+1] = z;
 
    for (int j = n-1; j >= i; j--)
        chaves[j+1] = chaves[j];
 
    chaves[i] = y->chaves[grau-1];

    n = n + 1;
}

InfoArvoreB **NoB::getChaves() {
    return this->chaves;
}

void NoB::setChaves(InfoArvoreB **chaves) {
    this->chaves = chaves;
}

int NoB::getGrau(){
    return this->grau;
}

void NoB::setGrau(int grau) {
    this->grau = grau;
}

int NoB::getN()  {
    return this->n;
}

void NoB::setN(int n) {
    this->n = n;
}

bool NoB::isFolha()  {
    return this->folha;
}

void NoB::setFolha(bool folha) {
    this->folha = folha;
}

NoB **NoB::getFilhos() {
    return this->filhos;
}

void NoB::setFilhos(NoB **filhos) {
    this->filhos = filhos;
}

int NoB::getNfilhos() {
    return this->nfilhos;
}

void NoB::setNfilhos(int nfilhos) {
    this->nfilhos = nfilhos;
}


