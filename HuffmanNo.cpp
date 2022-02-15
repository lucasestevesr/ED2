#include "HuffmanNo.h"

// Construtor
HuffmanNo::HuffmanNo(char dado, int frequencia) {
    this->dado = dado;
    this->frequencia = frequencia;
    this->esquerda = nullptr;
    this->direita = nullptr;
}

// Destrutor
HuffmanNo::~HuffmanNo() {}

// Início Getters e Setters
char HuffmanNo::getDado() {
    return this->dado;
}

void HuffmanNo::setDado(char dado) {
    this->dado = dado;
}

int HuffmanNo::getFrequencia() {
    return this->frequencia;
}

void HuffmanNo::setFrequencia(int frequencia) {
    this->frequencia = frequencia;
}

HuffmanNo *HuffmanNo::getEsquerda() {
    return this->esquerda;
}

void HuffmanNo::setEsquerda(HuffmanNo *esquerda) {
    this->esquerda = esquerda;
}

HuffmanNo *HuffmanNo::getDireita() {
    return this->direita;
}

void HuffmanNo::setDireita(HuffmanNo *direita) {
    this->direita = direita;
}
// Fim Getters e Setters

// Função para verificar se o Nó é folha
bool HuffmanNo::ehFolha() {
    return this->esquerda == nullptr && this->direita == nullptr;
}

// Imprimir Nos de forma encadeada
void HuffmanNo::imprimirDados(int arr[], int top) {
    if (this->esquerda != nullptr) {
        arr[top] = 0;
        imprimirDados(arr, top + 1);
    }

    if (this->direita != nullptr) {
        arr[top] = 1;
        imprimirDados(arr, top + 1);
    }

    if (this->ehFolha()) {
        cout << this->dado << ": ";
        imprimirDados(arr, top);
    }
}

// Imprimir array
void HuffmanNo::imprimirArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; ++i)
        cout<< arr[i];

    cout<<"\n";
}
