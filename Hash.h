#ifndef ED2_HASH_H
#define ED2_HASH_H

#include "HashEncadeado.h"

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
};

#endif //ED2_HASH_H
