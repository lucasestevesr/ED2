#include "Ordenar.h"

int Ordenar::particionamento(ReviewPonteiro *reviews, int ini, int fim, int *comparacoes, int *movimentacoes) {
    int pivo = Ordenar::medianaDeTres(reviews, ini, fim);

    int i = ini, j = fim-1;
    while(true)
    {
        while(i < fim && reviews[i]->getUpvotes() < pivo) {
            (*comparacoes)++;
            i++;
        }
        while(j >= ini && reviews[j]->getUpvotes() > pivo) {
            (*comparacoes)++;
            j--;
        }

        if(i < j) {
            swap(reviews[i], reviews[j]);
            (*movimentacoes)++;
            (*comparacoes)++;
            i++;
            j--;
        }
        else
            break;
    }
    swap(reviews[i], reviews[fim]);
    (*movimentacoes)++;
    return i;
}

int Ordenar::medianaDeTres(ReviewPonteiro *reviews, int ini, int fim) {
    int meio = (ini+fim)/2;
    if(reviews[ini]->getUpvotes() > reviews[fim]->getUpvotes())
        swap(reviews[ini], reviews[fim]);
    if(reviews[meio]->getUpvotes() > reviews[fim]->getUpvotes())
        swap(reviews[meio], reviews[fim]);
    if(reviews[ini]->getUpvotes() > reviews[meio]->getUpvotes())
        swap(reviews[ini], reviews[meio]);
    swap(reviews[meio], reviews[fim]);
    return reviews[fim]->getUpvotes();
}

void Ordenar::quickSort(ReviewPonteiro *reviews, int ini, int fim, int *comparacoes, int *movimentacoes) {
    if(ini < fim) {
        int p = Ordenar::particionamento(reviews, ini, fim, comparacoes, movimentacoes);
        Ordenar::quickSort(reviews, ini, p-1, comparacoes, movimentacoes);
        Ordenar::quickSort(reviews, p+1, fim, comparacoes, movimentacoes);
        return;
    }
}
