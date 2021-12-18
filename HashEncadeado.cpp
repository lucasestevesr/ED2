#include "HashEncadeado.h"

HashEncadeado::HashEncadeado() {
    this->inicio = nullptr;
    this->tamanho = 0;
}

HashEncadeado::~HashEncadeado() {
    while(this->inicio != NULL) {
        if(inicio->getProximo() != NULL) {
            HashNo *temp = inicio->getProximo();
            this->inicio->setProximo(NULL);
            delete this->inicio;
            this->inicio = temp;
        } else {
            this->inicio = NULL;
        }
    }
}

HashNo* HashEncadeado::getInicio() {
    return inicio;
}

void HashEncadeado::setInicio(HashNo *inicio) {
    this->inicio = inicio;
}

int HashEncadeado::getTamanho() {
    return tamanho;
}

void HashEncadeado::setTamanho(int tamanho) {
    this->tamanho = tamanho;
}

bool HashEncadeado::vazia() {
    return this->inicio == nullptr;
}

void HashEncadeado::inserir(string app_version) {
    HashNo *no = new HashNo(app_version, 1);
    no->setProximo(this->inicio);
    this->inicio = no;
    this->tamanho++;
}

HashNo* HashEncadeado::buscarHashNo(string app_version) {
    for(HashNo *noAtual = this->inicio; noAtual != nullptr; noAtual = noAtual->getProximo()) {
        if(noAtual->getAppVersion() == app_version) {
            return noAtual;
        }
    }
    return nullptr;
}

bool HashEncadeado::existeHashNo(string app_version) {
    for(HashNo *noAtual = this->inicio; noAtual != nullptr; noAtual = noAtual->getProximo()) {
        if(noAtual->getAppVersion() == app_version) {
            return true;
        }
    }
    return false;
}