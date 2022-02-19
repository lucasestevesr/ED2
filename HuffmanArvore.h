#ifndef ED2_HUFFMANARVORE_H
#define ED2_HUFFMANARVORE_H
#include "HuffmanHeap.h"
#include "HuffmanNo.h"

#define TAMANHO_MAXIMO 300

class HuffmanArvore {
    private:
        bool** codigosHuffman;
        int* tamanhosHuffman;
    public:
        HuffmanArvore();
        HuffmanHeap* criarEconstruirMinHeap(char *dados, int *frequencia, long tamanho);
        HuffmanNo* construirHuffmanArvore(char *dados, int *frequencia, long tamanho);
        void codificar(char *dados, int *frequencia, long tamanho);
        void salvarCodigos(HuffmanNo* root, int arr[], int top);
        void imprimirCodificado(HuffmanNo* root, int arr[], int top);
        void salvarArray(int *arr, int n, bool* codigo);
        void imprimirArray(int *arr, int n);
};

#endif //ED2_HUFFMANARVORE_H
