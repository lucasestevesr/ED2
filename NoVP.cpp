#include "NoVP.h"

// Construtor
NoVP::NoVP(string id, int localizacao) {
    this->id = id;
    this->localizacao = localizacao;
    this->cor = true;
    this->pai = nullptr;
    this->esquerdo = nullptr;
    this->direito = nullptr;
}

// Destrutor
NoVP::~NoVP() {
    this->id.clear();
}

// Getters e Setters
string NoVP::getId() {
    return this->id;
}

void NoVP::setId(string id) {
    this->id = id;
}

int NoVP::getLocalizacao() {
    return this->localizacao;
}

void NoVP::setLocalizacao(int localizacao) {
    this->localizacao = localizacao;
}

bool NoVP::isVermelho() {
    return this != nullptr && this->cor;
}

bool NoVP::isPreto() {
    if(this == nullptr)
        return true;
    return !this->cor;
}

void NoVP::setVermelho() {
    this->cor = true;
}

void NoVP::setPreto() {
    this->cor = false;
}

void NoVP::setCor(bool cor) {
    this->cor = cor;
}

NoVP *NoVP::getPai() {
    return this->pai;
}

void NoVP::setPai(NoVP *pai) {
    this->pai = pai;
}

NoVP *NoVP::getEsquerdo() {
    return this->esquerdo;
}

void NoVP::setEsquerdo(NoVP *esquerdo) {
    this->esquerdo = esquerdo;
}

NoVP *NoVP::getDireito() {
    return this->direito;
}

void NoVP::setDireito(NoVP *direito) {
    this->direito = direito;
}
// Fim Getters e Setters

// Função trocar cor do No
void NoVP::trocarCor() {
    this->cor = !this->isVermelho();
}
// Fim função trocar cor do No