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