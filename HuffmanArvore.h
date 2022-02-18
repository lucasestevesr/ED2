#ifndef ED2_HUFFMANARVORE_H
#define ED2_HUFFMANARVORE_H
#include "HuffmanHeap.h"
#include "HuffmanNo.h"

#define TAMANHO_MAXIMO 2000

class HuffmanArvore {
    public:
        static HuffmanHeap* criarEconstruirMinHeap(char *dados, int *frequencia, long tamanho);
        static HuffmanNo* construirHuffmanArvore(char *dados, int *frequencia, long tamanho);
        static void codificar(char *dados, int *frequencia, long tamanho);
        static void imprimirCodificado(HuffmanNo* root, int arr[], int top);
        static void imprimirArray(int *arr, int n);
};

#endif //ED2_HUFFMANARVORE_H
