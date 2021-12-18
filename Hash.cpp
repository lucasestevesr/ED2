#include "Hash.h"

Hash::Hash(int tamanho) {
    this->tamanho = tamanho;
    this->hashEncadeado = new HashEncadeadoPonteiro [tamanho];
    for(int i = 0; i < tamanho; i++) {
        this->hashEncadeado[i] = new HashEncadeado();
    }
}

Hash::~Hash() {
    for(int i = 0; i < tamanho; i++) {
        delete this->hashEncadeado[i];
    }
    delete [] this->hashEncadeado;
}

int Hash::getTamanho() {
    return this->tamanho;
}

void Hash::setTamanho(int tamanho) {
    this->tamanho = tamanho;
}

HashEncadeadoPonteiro* Hash::getHashEncadeado() {
    return this->hashEncadeado;
}

void Hash::setHashEncadeado(HashEncadeadoPonteiro *hashEncadeado) {
    this->hashEncadeado = hashEncadeado;
}
