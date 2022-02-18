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





void HuffmanHeap::insertMinHeap(HuffmanNo* minHeapNode) {
    ++this->tamanho;
    int i = this->tamanho - 1;

    while (i && minHeapNode->getFrequencia() < this->arrayNos[(i - 1) / 2]->getFrequencia()) {
        this->arrayNos[i] = this->arrayNos[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    this->arrayNos[i] = minHeapNode;
}

HuffmanNo* HuffmanHeap::extractMin() {
    HuffmanNo* temp = this->arrayNos[0];
    this->arrayNos[0] = this->arrayNos[this->tamanho - 1];

    --this->tamanho;
    minHeapify(0);

    return temp;
}

bool HuffmanHeap::isSizeOne() {
    return (this->tamanho == 1);
}

void HuffmanHeap::swapMinHeapNode(HuffmanNo** a, HuffmanNo** b) {
    HuffmanNo *t = *a;
    *a = *b;
    *b = t;
}

void HuffmanHeap::minHeapify(int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < this->tamanho && this->arrayNos[left]->getFrequencia() < this->arrayNos[smallest]->getFrequencia())
        smallest = left;

    if (right < this->tamanho && this->arrayNos[right]->getFrequencia() < this->arrayNos[smallest]->getFrequencia())
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&this->arrayNos[smallest], &this->arrayNos[idx]);
        minHeapify(smallest);
    }
}

void HuffmanHeap::buildMinHeap() {
    int n = this->tamanho - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(i);
}