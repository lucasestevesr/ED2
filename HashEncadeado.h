#ifndef ED2_HASHENCADEADO_H
#define ED2_HASHENCADEADO_H

#include "HashNo.h"

class HashEncadeado {
    private:
        HashNo *inicio;
        int tamanho;
public:
        HashEncadeado();
        ~HashEncadeado();
        HashNo* getInicio();
        void setInicio(HashNo *inicio);
        int getTamanho();
        void setTamanho(int tamanho);
        bool vazia();
        void inserir(string app_version);
        HashNo* buscarHashNo(string app_version);
        bool existeHashNo(string app_version);
};

#endif //ED2_HASHENCADEADO_H
