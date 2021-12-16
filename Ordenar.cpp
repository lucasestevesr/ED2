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

void Ordenar::heapify(ReviewPonteiro *reviews, int i, int n) {
    while(i < n) {
        int filho = 2*i + 1;
        if(filho < n) {
            if(filho+1 < n && reviews[filho+1]->getUpvotes() > reviews[filho]->getUpvotes())
                filho++;

            if(reviews[filho]->getUpvotes() > reviews[i]->getUpvotes())
                swap(reviews[i], reviews[filho]);
        }
        i = filho;
    }
}

void Ordenar::constroiHeap(ReviewPonteiro *reviews, int n) {
    for(int i = n/2-1; i >= 0; i--)
        Ordenar::heapify(reviews, i, n);
}

void Ordenar::heapSort(ReviewPonteiro *reviews, int n) {
    Ordenar::constroiHeap(reviews, n);
    while(n > 0) {
        swap(reviews[0], reviews[n-1]);
        Ordenar::heapify(reviews, 0, n-1);
        n--;
    }
}
