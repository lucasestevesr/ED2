#ifndef ED2_ORDENAR_H
#define ED2_ORDENAR_H

#include "Review.h"

typedef Review* ReviewPonteiro;

class Ordenar {
    public:
        static int particionamento(ReviewPonteiro *reviews, int ini, int fim, int *comparacoes, int *movimentacoes);
        static int medianaDeTres(ReviewPonteiro *reviews, int ini, int fim);
        static void quickSort(ReviewPonteiro *reviews, int ini, int fim, int *comparacoes, int *movimentacoes);
        static void heapify(ReviewPonteiro *reviews, int i, int n, int *comparacoes, int *movimentacoes);
        static void constroiHeap(ReviewPonteiro *reviews, int n, int *comparacoes, int *movimentacoes);
        static void heapSort(ReviewPonteiro *reviews, int n, int *comparacoes, int *movimentacoes);
        static int obterMaiorValor(ReviewPonteiro *reviews, int n);
        static void countSort(ReviewPonteiro *reviews, int n, int exp, int maiorValor, int *comparacoes, int *movimentacoes);
        static void radixSort(ReviewPonteiro *reviews, int n, int *comparacoes, int *movimentacoes);
};

#endif //ED2_ORDENAR_H