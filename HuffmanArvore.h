#ifndef ED2_HUFFMANARVORE_H
#define ED2_HUFFMANARVORE_H
#include "HuffmanHeap.h"
#include "HuffmanNo.h"

class HuffmanArvore {
    private:
        HuffmanHeap *heap;
        HuffmanNo *esquerda;
        HuffmanNo *direita;
        HuffmanNo *topo;

    public:
        // Contrutor e destrutor
        HuffmanArvore();
        ~HuffmanArvore();
        // Getters e Setters
        HuffmanHeap *getHeap();
        void setHeap(HuffmanHeap *heap);
        HuffmanNo *getEsquerda();
        void setEsquerda(HuffmanNo *esquerda);
        HuffmanNo *getDireita();
        void setDireita(HuffmanNo *direita);
        HuffmanNo *getTopo();
        void setTopo(HuffmanNo *topo);
        // Funções para manusear a árvore
        HuffmanHeap* criarEconstruirMinHeap(char data[], int freq[], int size);
        HuffmanNo* construirArvore(char dado[], int frequencia[], int tamanho);
        void imprimirHuffmanCodes(char data[], int freq[], int size, int alturaMaximaArvore);
};

#endif //ED2_HUFFMANARVORE_H
