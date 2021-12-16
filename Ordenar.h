#ifndef ED2_ORDENAR_H
#define ED2_ORDENAR_H

#include "Review.h"

typedef Review* ReviewPonteiro;

class Ordenar {
    public:
        static int particionamento(ReviewPonteiro *reviews, int ini, int fim, int *comparacoes, int *movimentacoes);
        static int medianaDeTres(ReviewPonteiro *reviews, int ini, int fim);
        static void quickSort(ReviewPonteiro *reviews, int ini, int fim, int *comparacoes, int *movimentacoes);
};

#endif //ED2_ORDENAR_H