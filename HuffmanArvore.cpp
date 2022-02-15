#include "HuffmanArvore.h"

// Contrutor
HuffmanArvore::HuffmanArvore() {
    this->heap = nullptr;
    this->esquerda = nullptr;
    this->direita = nullptr;
    this->topo = nullptr;
}

// Destrutor
HuffmanArvore::~HuffmanArvore() {}

// Início Getters e Setters
HuffmanHeap *HuffmanArvore::getHeap() {
    return this->heap;
}

void HuffmanArvore::setHeap(HuffmanHeap *heap) {
    this->heap = heap;
}

HuffmanNo *HuffmanArvore::getEsquerda() {
    return this->esquerda;
}

void HuffmanArvore::setEsquerda(HuffmanNo *esquerda) {
    this->esquerda = esquerda;
}

HuffmanNo *HuffmanArvore::getDireita() {
    return this->direita;
}

void HuffmanArvore::setDireita(HuffmanNo *direita) {
    this->direita = direita;
}

HuffmanNo *HuffmanArvore::getTopo() {
    return this->topo;
}

void HuffmanArvore::setTopo(HuffmanNo *topo) {
    this->topo = topo;
}
// Fim Getters e Setters

// Função para criar e construir a min Heap
HuffmanHeap* HuffmanArvore::criarEconstruirMinHeap(char data[], int freq[], int size) {
    HuffmanHeap *minHeap = new HuffmanHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->setNoArrayNos(new HuffmanNo(data[i], freq[i]), i);

    minHeap->setTamanho(size);
    minHeap->construirMinHeap();

    return minHeap;
}

// Construir árvore com os dados, as frequencias e o tamanho
HuffmanNo* HuffmanArvore::construirArvore(char dado[], int frequencia[], int tamanho) {
    HuffmanNo *esquerda, *direita, *topo;

    HuffmanHeap *minHeap = criarEconstruirMinHeap(dado, frequencia, tamanho);

    while(!minHeap->temTamanhoUm()) {
        esquerda = minHeap->getNoValorMinimo();
        direita = minHeap->getNoValorMinimo();

        topo = new HuffmanNo('$', esquerda->getFrequencia() + direita->getFrequencia());

        topo->setEsquerda(esquerda);
        topo->setDireita(direita);

        minHeap->inserirNo(topo);
    }

    return minHeap->getNoValorMinimo();
}

// Imprimir Huffman codes
void HuffmanArvore::imprimirHuffmanCodes(char data[], int freq[], int size, int alturaMaximaArvore) {
    HuffmanNo* root = construirArvore(data, freq, size);

    int arr[alturaMaximaArvore], top = 0;

    printCodes(root, arr, top);
}
