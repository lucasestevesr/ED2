#include "HuffmanHeap.h"

// Construtor
// createMinHeap
HuffmanHeap::HuffmanHeap(long capacidade) {
    this->capacidade = capacidade;
    this->tamanho = 0;
    this->raiz = nullptr;
    this->arrayNos = new HuffmanNo*[capacidade];
}

// Destrutor
HuffmanHeap::~HuffmanHeap() {
    for(int i = 0; i < this->tamanho; i++) {
        if(this->arrayNos[i] != nullptr) {
            delete arrayNos[i];
        }
    }
    delete [] arrayNos;
}

// Início Getters e Setters
long HuffmanHeap::getTamanho() {
    return this->tamanho;
}

void HuffmanHeap::setTamanho(long tamanho) {
    this->tamanho = tamanho;
}

long HuffmanHeap::getCapacidade() {
    return this->capacidade;
}

void HuffmanHeap::setCapacidade(long capacidade) {
    this->capacidade = capacidade;
}

HuffmanNo *HuffmanHeap::getRaiz() {
    return this->raiz;
}

void HuffmanHeap::setRaiz(HuffmanNo *raiz) {
    this->raiz = raiz;
}

HuffmanNo **HuffmanHeap::getArrayNos() {
    return this->arrayNos;
}

void HuffmanHeap::setArrayNos(HuffmanNo **arrayNos) {
    this->arrayNos = arrayNos;
}

void HuffmanHeap::setNoArrayNos(HuffmanNo *no, int indice) {
    this->arrayNos[indice] = no;
}
// Fim Getters e Setters




//




// Funcao responsavel por inserir um novo no na minHep
void HuffmanHeap::insertMinHeap(HuffmanNo* minHeapNode, int *comparacoes) {
    // incrementa total de elementos na heap
    ++this->tamanho;
    int i = this->tamanho - 1;

    (*comparacoes) += 2;
    while (i && minHeapNode->getFrequencia() < this->arrayNos[(i - 1) / 2]->getFrequencia()) {
        (*comparacoes) += 2;
        this->arrayNos[i] = this->arrayNos[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    this->arrayNos[i] = minHeapNode;
}

// Recupera o no de valor minimo na heap
HuffmanNo* HuffmanHeap::extractMin(int *comparacoes) {
    HuffmanNo* temp = this->arrayNos[0];
    this->arrayNos[0] = this->arrayNos[this->tamanho - 1];

    --this->tamanho;
    minHeapify(0, comparacoes);

    return temp;
}

bool HuffmanHeap::isSizeOne() {
    return (this->tamanho == 1);
}
// Função responsavel por inverter dois nos
void HuffmanHeap::swapMinHeapNode(HuffmanNo** a, HuffmanNo** b) {
    // no auxiliar
    HuffmanNo *t = *a;
    *a = *b;
    *b = t;
}

// Função responsavel por auxiliar a construcao da Heap
void HuffmanHeap::minHeapify(int idx, int *comparacoes) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    // verificando se o elemento deve trocar de posicao com o elemento da esquerda
    (*comparacoes) += 2;
    if (left < this->tamanho && this->arrayNos[left]->getFrequencia() < this->arrayNos[smallest]->getFrequencia())
        smallest = left;

    // verificando se o elemento deve trocar de posicao com o elemento da direira
    (*comparacoes) += 2;
    if (right < this->tamanho && this->arrayNos[right]->getFrequencia() < this->arrayNos[smallest]->getFrequencia())
        smallest = right;

    (*comparacoes) += 1;
    if (smallest != idx) {
        // inverte os dois nos
        swapMinHeapNode(&this->arrayNos[smallest], &this->arrayNos[idx]);
        // chama recursivo para o novo valor de smallest
        minHeapify(smallest, comparacoes);
    }
}

// Função responsavel por construir a minHeap
void HuffmanHeap::buildMinHeap(int *comparacoes) {
    int n = this->tamanho - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(i, comparacoes);
}