#include <iostream>
#include "NoB.h"

using namespace std;


NoB::NoB(int grau, bool folha, int nfilhos) { // Construtor padrão do nó
    this->grau = grau;
    this->folha = folha;
    this->chaves = new InfoArvoreB[nfilhos];
    this->filhos = new NoB *[nfilhos+1];
    this->n = 0;
    this->nfilhos = nfilhos;
}

NoB::~NoB() {
    delete [] this->chaves;
    delete [] this->filhos;
}

// Função que percorre todos os nós pertencentes a um nó específico 

void NoB::percorreNos() {

    int i;
    for (i = 0; i < n; i++) {

        if (!folha){
            filhos[i]->percorreNos();
        }
        cout << " " << chaves[i].id;
    }
 
    if (!folha)
        filhos[i]->percorreNos();
}
 
// Busca uma chave específica em um determinado nó

NoB *NoB::buscaNo(string k, int *comparacoes) {

    int i = 0;                      
    while (i < n && k > chaves[i].id) { // busca entre total de chaves alguma maior ou igual
        (*comparacoes)++; // added 
        i++;
    }

    if (chaves[i].id == k){         // verfica se o id do registro eh igual ao passado p/ função
        (*comparacoes)++; // added    
        return this;
    }

    if (folha)                      // verifica se o nó eh folha
        return nullptr;
 
    return filhos[i]->buscaNo(k, comparacoes);   // continua buscando em seus filhos
}

// Função que insere um no na subarvore daquele nó desde que o nó tenha espaço para inserir uma nova chave

void NoB::insereNoComEspaco(string k, int localizacao, int *comparacoes) { // added
    int i = n-1;        // a busca pela posição nas chaves será feita a partir da direita              

    if (folha) {

        // abrindo espaços no array de chaves do nó
        while (i >= 0 && chaves[i].id > k) {
            (*comparacoes)++; // added
            chaves[i+1] = chaves[i];
            i--;
        }
        // inserindo o novo registro nas chaves
        chaves[i+1].id = k;
        chaves[i+1].localizacao = localizacao;
        n = n+1;            // incrementando elementos da chave
    }else {
        // buscando o filho que receberá o novo nó
        while (i >= 0 && chaves[i].id > k) {
            (*comparacoes)++; // added
            i--;
        }

        // verificando se o filho possui espaço 
        if (filhos[i+1]->getN() == nfilhos) {
            (*comparacoes)++; // added
            // se estiver cheio, particione-o
            particionaNoFilho(i+1, filhos[i+1]);

            // o elemento do meio sobe e também é selecionado qual das partes receberá o novo nó
            if (chaves[i+1].id < k)
                (*comparacoes)++; // added
                i++;
        }
        filhos[i+1]->insereNoComEspaco(k, localizacao, comparacoes); // added
    }
}
 
// função utilizada para inserir um nó quando o filho de um determinado nó estiver totalmente cheio.
void NoB::particionaNoFilho(int i, NoB *y) {

    // nó que vai receber um total de grau - 1 chaves de y
    NoB *z = new NoB(y->grau, y->folha, y->nfilhos);
    z->n = grau - 1;
    
    // atribuindo os nós de y para z
    for (int j = 0; j < grau-1; j++)
        z->chaves[j] = y->chaves[j+grau];
    
    // copiando também os filhos de y para os filhos de z
    if (!y->folha) {
        for (int j = 0; j < grau; j++) 
            z->filhos[j] = y->filhos[j+grau];
    }

    // atualizando o total de chaves
    y->n = grau - 1;

    // abrindo espaço em seus filhos para inserir um novo filho
    for (int j = n; j >= i+1; j--) {
        filhos[j+1] = filhos[j];
    }
    
    // inserindo novo filho
    filhos[i+1] = z;
    
    // também é necessario abrir espaços no array de chaves do nó para inserir uma chave de y
    for (int j = n-1; j >= i; j--) 
        chaves[j+1] = chaves[j];
    
    
    // após abrir espaço no array de chaves, é possível inserir uma chave de y
    chaves[i] = y->chaves[grau-1];

    // atualizando o total de chaves no nó
    n = n + 1;
}

// getters e setters 

InfoArvoreB *NoB::getChaves() {
    return this->chaves;
}

void NoB::setChaves(InfoArvoreB *chaves) {
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


