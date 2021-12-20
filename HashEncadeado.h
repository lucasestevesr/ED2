#ifndef ED2_HASHENCADEADO_H
#define ED2_HASHENCADEADO_H

#include "HashNo.h"
#include <iostream>

class HashEncadeado {
    private:
        // Atributos
        HashNo *inicio;
        int tamanho;
        // Fim Atributos
    public:
        // Contrutor
        HashEncadeado();
        // Destrutor
        ~HashEncadeado();
        // Getters e setters
        HashNo* getInicio();
        void setInicio(HashNo *inicio);
        int getTamanho();
        void setTamanho(int tamanho);
        // Fim Getters e setters
        // Verificar lista vazia
        bool vazia();
        // Inserir no inicio da lista
        void inserir(string app_version);
        // Buscar No pela app version
        HashNo* buscarHashNo(string app_version);
        // Imprimir lista encadeada
        void imprimir();
};

#endif //ED2_HASHENCADEADO_H
