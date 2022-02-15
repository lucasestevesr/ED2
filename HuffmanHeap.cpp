#include "HuffmanHeap.h"

// Construtor
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
void HuffmanHeap::heapifyMinimo(int indice) {
    int smallest = indice;
    int left = 2 * indice + 1;
    int right = 2 * indice + 2;

    if (left < this->tamanho && this->arrayNos[left]->getFrequencia() < this->arrayNos[smallest]->getFrequencia())
        smallest = left;

    if (right < this->tamanho && this->arrayNos[right]->getFrequencia() < this->arrayNos[smallest]->getFrequencia())
        smallest = right;

    if (smallest != indice) {
        escolherMenorNo(&this->arrayNos[smallest], &this->arrayNos[indice]);
        heapifyMinimo(smallest);
    }
}

// Função para escolher o menor Nó e fazer a troca
void HuffmanHeap::escolherMenorNo(HuffmanNo **a, HuffmanNo **b) {
    HuffmanNo* t = *a;
    *a = *b;
    *b = t;
}

// Função para criar novo nó
HuffmanNo* HuffmanHeap::criarNovoNo(char dado, int frequencia) {
    HuffmanNo* novo_no = new HuffmanNo(dado, frequencia);

    novo_no->setEsquerda(nullptr);
    novo_no->setDireita(nullptr);

    return novo_no;
}

// Função verificar se o tamanho da Heap é 1
bool HuffmanHeap::temTamanhoUm() {
    return (this->tamanho == 1);
}

// Função recuperar o Nó de valor mínimo no Heap
HuffmanNo* HuffmanHeap::getNoValorMinimo() {
    HuffmanNo *no = this->arrayNos[0];
    this->arrayNos[0] = this->arrayNos[this->tamanho - 1];

    this->tamanho = this->tamanho - 1;
    heapifyMinimo(0);

    return no;
}

// Função inserir HuffmanNo no HuffmanHeap
void HuffmanHeap::inserirNo(HuffmanNo* minHeapNo) {
    this->tamanho = this->tamanho + 1;
    int i = this->tamanho - 1;

    while (i && minHeapNo->getFrequencia() < this->arrayNos[(i - 1) / 2]->getFrequencia()) {
        this->arrayNos[i] = this->arrayNos[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    this->arrayNos[i] = minHeapNo;
}

// Função construir a min Heap
void HuffmanHeap::construirMinHeap() {
    int n = this->tamanho - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        heapifyMinimo(i);
}