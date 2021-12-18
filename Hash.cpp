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

int Hash::getChave(string app_version) {
    unsigned long hash = 5381;
    for (int i = 0; i < app_version.size(); ++i) {
        hash = 33 * hash + (unsigned char)app_version[i];
    }
    return hash % this->tamanho;
}

void Hash::inserir(Review *review) {
    int chave = Hash::getChave(review->getAppVersion());

    HashNo *hashNo = this->hashEncadeado[chave]->buscarHashNo(review->getAppVersion());

    if(hashNo == nullptr) {
        this->hashEncadeado[chave]->inserir(review->getAppVersion());
    } else {
        hashNo->setFrequencia(hashNo->getFrequencia() + 1);
    }
}

void Hash::imprimirFrequentes(int qnt) {
    int a = 0, b = 0;
    for (int i = 0; i < this->tamanho; ++i) {
        if(!this->hashEncadeado[i]->vazia()) {
            a += this->hashEncadeado[i]->getTamanho();
            if(this->hashEncadeado[i]->getTamanho() > 1) {
                b += this->hashEncadeado[i]->getTamanho() - 1;
            }
        }
    }
    cout << "A: " << a << endl;
    cout << "B: " << b << endl;
}
