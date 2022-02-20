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
        double tamanhoComprimido;
        double tamanhoOriginal;
        HuffmanNo *raiz;
        HuffmanHeap *minHeap;

    public:
        HuffmanArvore(long tamanhoOriginal);
        ~HuffmanArvore();
        double getTamanhoComprimido();
        HuffmanHeap* criarEconstruirMinHeap(char *dados, long *frequencia, long tamanho, int *comparacoes);
        HuffmanNo* construirHuffmanArvore(char *dados, long *frequencia, long tamanho, int *comparacoes);
        void codificar(char *dados, long *frequencia, long tamanho, int *comparacoes);
        void salvarCodigos(HuffmanNo* root, int arr[], int top);
        void imprimirCodificado(HuffmanNo* root, int arr[], int top);
        void salvarArray(int *arr, int n, bool* codigo);
        void imprimirArray(int *arr, int n);
        bool* comprimirHuffman(char *letras, long *frequencias, string reviews_texts);
        void salvarTamanhos(char *letras, long *frequencias);
        string descomprimirHuffman(bool *comprimido);
};

#endif //ED2_HUFFMANARVORE_H
