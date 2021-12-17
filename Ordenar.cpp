#include "Ordenar.h"

// Inicio função particionamento usada no quickSort
int Ordenar::particionamento(ReviewPonteiro *reviews, int ini, int fim, int *comparacoes, int *movimentacoes) {
    int pivo = Ordenar::medianaDeTres(reviews, ini, fim, comparacoes, movimentacoes);

    int i = ini, j = fim-1;
    do {
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
            i++;
            j--;
        }
    }while(i < j);

    swap(reviews[i], reviews[fim]);
    (*movimentacoes)++;

    return i;
}
// Fim função particionamento usada no quickSort

// Inicio função para pegar o pivo do quickSort
int Ordenar::medianaDeTres(ReviewPonteiro *reviews, int ini, int fim, int *comparacoes, int *movimentacoes) {
    int meio = (ini+fim)/2;

    if(reviews[ini]->getUpvotes() > reviews[fim]->getUpvotes()) {
        swap(reviews[ini], reviews[fim]);
        (*comparacoes)++;
        (*movimentacoes)++;
    }
    if(reviews[meio]->getUpvotes() > reviews[fim]->getUpvotes()) {
        swap(reviews[meio], reviews[fim]);
        (*comparacoes)++;
        (*movimentacoes)++;
    }
    if(reviews[ini]->getUpvotes() > reviews[meio]->getUpvotes()) {
        swap(reviews[ini], reviews[meio]);
        (*comparacoes)++;
        (*movimentacoes)++;
    }

    swap(reviews[meio], reviews[fim]);
    (*comparacoes)++;
    (*movimentacoes)++;

    return reviews[fim]->getUpvotes();
}
// Fim função para pegar o pivo do quickSort

// Inicio função de ordenação quickSort
void Ordenar::quickSort(ReviewPonteiro *reviews, int ini, int fim, int *comparacoes, int *movimentacoes) {
    if(ini < fim) {
        int p = Ordenar::particionamento(reviews, ini, fim, comparacoes, movimentacoes);
        Ordenar::quickSort(reviews, ini, p-1, comparacoes, movimentacoes);
        Ordenar::quickSort(reviews, p+1, fim, comparacoes, movimentacoes);
    }
}
// Fim função de ordenação quickSort

// Inicio função para fazer as comparações e trocas na heapSort
void Ordenar::heapify(ReviewPonteiro *reviews, int i, int n, int *comparacoes, int *movimentacoes) {
    while(i < n) {
        int filho = 2*i + 1;
        if(filho < n) {
            if(filho+1 < n && reviews[filho+1]->getUpvotes() > reviews[filho]->getUpvotes()){
                filho++;
                (*comparacoes)++;
            }
            if(reviews[filho]->getUpvotes() > reviews[i]->getUpvotes()){
                swap(reviews[i], reviews[filho]);
                (*movimentacoes)++;
            }
        }
        i = filho;
    }
}
// Fim função para fazer as comparações e trocas na heapSort

// Inicio funcao para constuir ordenação da heap
void Ordenar::constroiHeap(ReviewPonteiro *reviews, int n, int *comparacoes, int *movimentacoes) {
    for(int i = n/2-1; i >= 0; i--) {
        Ordenar::heapify(reviews, i, n, comparacoes, movimentacoes);
    }
}
// Fim funcao para constuir ordenação da heap

// Inicio função principal da ordenação heapSort
void Ordenar::heapSort(ReviewPonteiro *reviews, int n, int *comparacoes, int *movimentacoes) {
    Ordenar::constroiHeap(reviews, n, comparacoes, movimentacoes);
    while(n > 0) {
        swap(reviews[0], reviews[n-1]);
        Ordenar::heapify(reviews, 0, n-1, comparacoes, movimentacoes);
        n--;
    }
}
// Fim função principal da ordenação heapSort

// Inicio função obter maior valor de um vetor
int Ordenar::obterMaiorValor(ReviewPonteiro *reviews, int n) {
    // Esta função garante que foi recuperado o valor com maior de quantidade de algarismos dentro dentre todos os indices possíveis do vetor
    // Começa o menor como o primeiro
    int maior = reviews[0]->getUpvotes();
    // Percorre o vetor
    for (int i = 1; i < n; i++) {
        // Se encotrar algum melhor troca o maior
        if (reviews[i]->getUpvotes() > maior) {
            maior = reviews[i]->getUpvotes();
        }
    }
    return maior;
}
// Fim função obter maior valor de um vetor

// Inicio função countSort usada no RadixSort para ordenar considerando somente um algarismo
void Ordenar::countSort(ReviewPonteiro *reviews, int n, int exp, int maiorValor, int *comparacoes, int *movimentacoes) {
    ReviewPonteiro *output = new ReviewPonteiro[n];
    int ultimoIndice = maiorValor + 1;
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
        (*movimentacoes)++;
        // Recupera cada algarismo dentro de um determinado indice
        count[(reviews[i]->getUpvotes() / exp) % 10]--;
    }

    // O array de saida recebe em cada um de seus indices os elementos do array output, sendo que output já foi ordenado de acordo com a posição do algarismo atual  
    for (int i = 0; i < n; i++) {
        reviews[i] = output[i];
        (*movimentacoes)++;
    }

    // Deleta o array output pois o novo array que será iterado está com seus elementos atualizados (reviews[]), sendo output, um array auxiliar
    delete [] output;
    delete [] count;
}
// Fim função countSort usada no RadixSort para ordenar considerando somente um algarismo

// Inicio função de ordenação radixSort
void Ordenar::radixSort(ReviewPonteiro *reviews, int n, int *comparacoes, int *movimentacoes) {
    int maiorValor = Ordenar::obterMaiorValor(reviews, n);
    (*comparacoes) += n;

    // Enquanto o total de unidades de um indice for maior que 0, para avançar em uma casa decimal para esquerda dentro deste indice, exp precisa ser um multiplo de 10 para fazer a divisão do indice
    for (int exp = 1; maiorValor / exp > 0; exp *= 10) {
        Ordenar::countSort(reviews, n, exp, maiorValor, comparacoes, movimentacoes);
    }
}
// Fim função de ordenação radixSort