#include <iostream>
#include "NoB.h"

using namespace std;


NoB::NoB(int grau, bool folha) {

    this->grau = grau;
    this->folha = folha;
    this->chaves = new string[2*grau-1];
    this->filhos = new NoB *[2*grau];
    this->n = 0;
}

NoB::~NoB() {}

// Função que percorre todos os nós pertencentes a um nó específico 

void NoB::percorreNos() {

    int i;
    for (i = 0; i < n; i++) {

        if (folha == false)
            filhos[i]->percorreNos();
        cout << " " << chaves[i];
    }
 
    if (folha == false)
        filhos[i]->percorreNos();
}
 
// Busca uma chave específica em um determinado nó

NoB *NoB::buscaNo(string k) {

    int i = 0;
    while (i < n && k > chaves[i])
        i++;

    if (chaves[i] == k){
        cout << chaves[i] << endl;
        cout << k << endl;
        return this;
    }

 
    if (folha == true)
        return nullptr;
 
    return filhos[i]->buscaNo(k);
}

// Função que insere um no na subarvore daquele nó desde que o nó tenha espaço para inserir uma nova chave

void NoB::insereNoComEspaco(string k) {

    int i = n-1;
    if (folha == true) {

        while (i >= 0 && chaves[i] > k) {
            chaves[i+1] = chaves[i];
            i--;
        }
        chaves[i+1] = k;
        n = n+1;
    }
    else 
    {
        while (i >= 0 && chaves[i] > k)
            i--;
 
        if (filhos[i+1]->n == 2*grau-1) {
            particionaNoFilho(i+1, filhos[i+1]);
 
            if (chaves[i+1] < k)
                i++;
        }
        filhos[i+1]->insereNoComEspaco(k);
    }
}
 
// função utilizada para inserir um nó quando o filho de um determinado nó estiver totalmente cheio.
void NoB::particionaNoFilho(int i, NoB *y) {

    NoB *z = new NoB(y->grau, y->folha);
    z->n = grau - 1;
 
    for (int j = 0; j < grau-1; j++)
        z->chaves[j] = y->chaves[j+grau];
 
    if (y->folha == false) {
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

string *NoB::getChaves() {
    return this->chaves;
}

void NoB::setChaves(string *chaves) {
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

int NoB::getLocalizacao() {
    return this->localizacao;
}

void NoB::setLocalizacao(int localizacao) {
    this->localizacao = localizacao;
}
