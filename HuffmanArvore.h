#ifndef ED2_HUFFMANARVORE_H
#define ED2_HUFFMANARVORE_H
#include "HuffmanHeap.h"
#include "HuffmanNo.h"

#define TAMANHO_MAXIMO 256
#define METADE_MAXIMO 128

class HuffmanArvore {
    private:
        bool** codigosHuffman;
        int* tamanhosHuffman;
        long tamanhoComprimido;
        long tamanhoOriginal;
        HuffmanNo *raiz;
        HuffmanHeap *minHeap;

    public:
        HuffmanArvore(long tamanhoOriginal);
        ~HuffmanArvore();
        long getTamanhoComprimido();
        HuffmanHeap* criarEconstruirMinHeap(char *dados, int *frequencia, long tamanho);
        HuffmanNo* construirHuffmanArvore(char *dados, int *frequencia, long tamanho);
        void codificar(char *dados, int *frequencia, long tamanho);
        void salvarCodigos(HuffmanNo* root, int arr[], int top);
        void imprimirCodificado(HuffmanNo* root, int arr[], int top);
        void salvarArray(int *arr, int n, bool* codigo);
        void imprimirArray(int *arr, int n);
        bool* comprimirHuffman(char *letras, int *frequencias, string reviews_texts);
        void salvarTamanhos(char *letras, int *frequencias);
        string descomprimirHuffman(bool *comprimido);
};

#endif //ED2_HUFFMANARVORE_H
