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
        void setNoArrayNos(HuffmanNo *no, int indice);

        // Funções para manusear a árvore
        void insertMinHeap(HuffmanNo* minHeapNode, int *comparacoes);
        HuffmanNo* extractMin(int *comparacoes);
        bool isSizeOne();
        void swapMinHeapNode(HuffmanNo** a, HuffmanNo** b);
        void minHeapify(int idx, int *comparacoes);
        void buildMinHeap(int *comparacoes);
};

#endif //ED2_HUFFMANHEAP_H
