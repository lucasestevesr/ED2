#ifndef ED2_HUFFMANNO_H
#define ED2_HUFFMANNO_H
#include <iostream>

using namespace std;

class HuffmanNo {
    private:
        char dado;
        int frequencia;
        HuffmanNo *esquerda;
        HuffmanNo *direita;

    public:
        // Construtor e destrutor
        HuffmanNo(char dado, int frequencia);
        ~HuffmanNo();
        // Getters e Setters
        char getDado();
        void setDado(char dado);
        int getFrequencia();
        void setFrequencia(int frequencia);
        HuffmanNo *getEsquerda();
        void setEsquerda(HuffmanNo *esquerda);
        HuffmanNo *getDireita();
        void setDireita(HuffmanNo *direita);
        // Função para verificar se o Nó é folha
        bool ehFolha();
        // Imprimir Nos de forma encadeada
        void imprimirDados(int arr[], int top);
        void imprimirArray(int arr[], int n);

};

#endif //ED2_HUFFMANNO_H
