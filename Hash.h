#ifndef ED2_HASH_H
#define ED2_HASH_H

#include <iostream>
#include "HashEncadeado.h"
#include "Review.h"

typedef HashEncadeado* HashEncadeadoPonteiro;

class Hash {
    private:
        int tamanho;
        HashEncadeadoPonteiro *hashEncadeado;
    public:
        Hash(int tamanho);
        ~Hash();
        int getTamanho();
        void setTamanho(int tamanho);
        HashEncadeadoPonteiro* getHashEncadeado();
        void setHashEncadeado(HashEncadeadoPonteiro *hashEncadeado);
        int getChave(string app_version);
        void inserir(string app_version);
        void imprimir();
        void imprimirOrdenado(int qnt);
        int recuperarQuantidadeNos();
        int* transformarVetorFrequencia(int tamanho);
        string* transformarVetorAppVersion(int tamanho);
};

#endif //ED2_HASH_H
