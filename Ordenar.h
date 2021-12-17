#ifndef ED2_ORDENAR_H
#define ED2_ORDENAR_H

#include "Review.h"

typedef Review* ReviewPonteiro;

class Ordenar {
    public:
        // Função particionamento usada no quickSort
        static int particionamento(ReviewPonteiro *reviews, int ini, int fim, int *comparacoes, int *movimentacoes);
        // Função para pegar o pivo do quickSort
        static int medianaDeTres(ReviewPonteiro *reviews, int ini, int fim, int *comparacoes, int *movimentacoes);
        // Função de ordenação quickSort
        static void quickSort(ReviewPonteiro *reviews, int ini, int fim, int *comparacoes, int *movimentacoes);
        // Função para fazer as comparações e trocas na heapSort
        static void heapify(ReviewPonteiro *reviews, int i, int n, int *comparacoes, int *movimentacoes);
        // Função para constuir ordenação da heap
        static void constroiHeap(ReviewPonteiro *reviews, int n, int *comparacoes, int *movimentacoes);
        // Função principal da ordenação heapSort
        static void heapSort(ReviewPonteiro *reviews, int n, int *comparacoes, int *movimentacoes);
        // Função obter maior valor de um vetor
        static int obterMaiorValor(ReviewPonteiro *reviews, int n);
        // Função countSort usada no RadixSort para ordenar considerando somente um algarismo
        static void countSort(ReviewPonteiro *reviews, int n, int exp, int maiorValor, int *comparacoes, int *movimentacoes);
        // Função de ordenação radixSort
        static void radixSort(ReviewPonteiro *reviews, int n, int *comparacoes, int *movimentacoes);
};

#endif //ED2_ORDENAR_H