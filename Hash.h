#ifndef ED2_HASH_H
#define ED2_HASH_H

#include <iostream>
#include <fstream>
#include "HashEncadeado.h"
#include "Review.h"

typedef HashEncadeado* HashEncadeadoPonteiro;

class Hash {
    private:
        // Atributos
        int tamanho;
        HashEncadeadoPonteiro *hashEncadeado;
        // Fim Atributos
    public:
        // Construtor
        Hash(int tamanho);
        // Destrutor
        ~Hash();
        // Getters e Setters
        int getTamanho();
        void setTamanho(int tamanho);
        HashEncadeadoPonteiro* getHashEncadeado();
        void setHashEncadeado(HashEncadeadoPonteiro *hashEncadeado);
        // Fim Getters e Setters
        // Funcao da formula do hash para retorna a chave
        int getChave(string app_version);
        // Inserir string na tabela Hash
        void inserir(string app_version);
        // Imprimir tabela hash
        void imprimir();
        // Ordenar e imprimir tabela Hash ordenada
        void imprimirOrdenado(int qnt);
        // Ordenar e escrever tabela Hash ordenada em arquivo
        void imprimirArquivo(ofstream &arquivo_testes);
        // Recuperar quantidade de Nos tem na tabela
        int recuperarQuantidadeNos();
        // Criar vetor de frequencias com todos valores da tabela
        int* transformarVetorFrequencia(int tamanho);
        // Criar vetor de strings de app version da tabela
        string* transformarVetorAppVersion(int tamanho);
};

#endif //ED2_HASH_H
