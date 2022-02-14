#ifndef ED2_HUFFMANHEAP_H
#define ED2_HUFFMANHEAP_H
#include "HuffmanNo.h"

class HuffmanHeap {
    private:
        long tamanho;
        long capacidade;
        HuffmanNo *raiz;
        HuffmanNo **arrayNos;

    public:
        // Construtor e destrutor
        HuffmanHeap(long capacidade);
        ~HuffmanHeap();
        // Getters e Setters
        long getTamanho();
        void setTamanho(long tamanho);
        long getCapacidade();
        void setCapacidade(long capacidade);
        HuffmanNo *getRaiz();
        void setRaiz(HuffmanNo *raiz);
        HuffmanNo **getArrayNos();
        void setArrayNos(HuffmanNo **arrayNos);
        // Funções para manusear a árvore
        void heapifyMinimo(int indice);
        void escolherMenorNo(HuffmanNo **a, HuffmanNo **b);
        HuffmanNo* criarNovoNo(char dado, int frequencia);
        bool temTamanhoUm();
        HuffmanNo* getNoValorMinimo();
        void inserirNo(HuffmanNo* minHeapNo);
        void construirMinHeap();
        HuffmanHeap* criarEconstruirMinHeap(char data[], int freq[], int size);
};

#endif //ED2_HUFFMANHEAP_H
