#include <iostream>
#include "NoB.h"

using namespace std;

// construtor 

NoB::NoB(int ordem, bool ehFolha) {

    grau = ordem;
    chaves = new int[2*ordem-1];
    filhos = new NoB *[2*ordem];
    totalNos = 0; // numero de chaves
    ehFolha = ehFolha; 
};

// destrutor

NoB::~NoB() {};

// verifica se o no eh folha

bool NoB::getEhFolha() {
   
    return ehFolha;
}

// retorna o total de nos 

int NoB::getTotalNos() {
    
    return totalNos;
}

// busca um determinado no a partir do indice passado

NoB* NoB::buscaNo(int indice) {
    
    int i = 0;
    while(i < totalNos && indice > chaves[i]) {
        i++;
    }

    if(getEhFolha()) {
        
        return NULL;
    }

    if(chaves[i] == indice) {

        return this;
    }

    return filhos[i]->buscaNo(indice);
};

// busca um chave em um nó a partir de seu indice

int NoB::buscaChaveNo(int indice) {
    
    int aux = 0;
    while (aux < totalNos && chaves[aux] < indice)
        aux++;
    return aux;
}

// atualiza o total de nos

void NoB::incrementaTotalNos() {

    totalNos++;
}