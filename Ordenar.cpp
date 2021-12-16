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

// Esta função garante que foi recuperado o valor com maior de quantidade de algarismos dentro dentre todos os indices possíveis do vetor
int Ordenar::obterMaiorValor(ReviewPonteiro *reviews, int n) {
    int maior = reviews[0]->getUpvotes();
    for (int i = 1; i < n; i++) {
        if (reviews[i]->getUpvotes() > maior) {
            maior = reviews[i]->getUpvotes();
        }
    }
    return maior;
}

void Ordenar::countSort(ReviewPonteiro *reviews, int n, int exp) {
    ReviewPonteiro *output = new ReviewPonteiro[n];
    int maior = Ordenar::obterMaiorValor(reviews, n);
    int ultimoIndice = maior + 1;
    int *count = new int[ultimoIndice];

    for(int i = 0; i < ultimoIndice; i++){
        count[i] = 0;
    }

    // Avança sobre cara valor dentro de um indice fazendo divisões sucessivas por 10 e recuperando a parte inteira no dono indice para fazer novas comparações
    for (int i = 0; i < n; i++) {
        count[(reviews[i]->getUpvotes() / exp) % 10]++;
    }

    // Após as comparações, um novo indice "i" é preenchido com base nos elementos já orenados do vetor na posição anterior "i-1", ou seja, o indice "i" do array, terá os mesmos elementos 
    for (int i = 1; i < ultimoIndice; i++) {
        count[i] += count[i - 1];
    }


    for (int i = n - 1; i >= 0; i--) {
        // Como o algoritmo utiliza a forma LSD(Least significant digit), os indices tem seus algarismos comparados da direita para a esquerda
        output[count[(reviews[i]->getUpvotes() / exp) % 10] - 1] = reviews[i];
        // Recupera cada algarismo dentro de um determinado indice
        count[(reviews[i]->getUpvotes() / exp) % 10]--;
    }

    // O array de saida recebe em cada um de seus indices os elementos do array output, sendo que output já foi ordenado de acordo com a posição do algarismo atual  
    for (int i = 0; i < n; i++) {
        reviews[i] = output[i];
    }

    // Deleta o array output pois o novo array que será iterado está com seus elementos atualizados (reviews[]), sendo output, um array auxiliar
    delete [] output;
}

void Ordenar::radixSort(ReviewPonteiro *reviews, int n) {
    int m = Ordenar::obterMaiorValor(reviews, n);

    // Enquanto o total de unidades de um indice for maior que 0, para avançar em uma casa decimal para esquerda dentro deste indice, exp precisa ser um multiplo de 10 para fazer a divisão do indice
    for (int exp = 1; m / exp > 0; exp *= 10) {
        Ordenar::countSort(reviews, n, exp);
    }
}
