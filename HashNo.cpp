#include "HashNo.h"

// Construtor
HashNo::HashNo(string app_version, int frequencia) {
    this->app_version = app_version;
    this->frequencia = frequencia;
}
// Fim Construtor

// Construtor Vazio
HashNo::HashNo() {}
// Fim Construtor Vazio

// Destrutor
HashNo::~HashNo() {
    this->app_version.clear();
}
// Fim Destrutor

// Getters e Setters
int HashNo::getFrequencia() {
    return this->frequencia;
}

void HashNo::setFrequencia(int frequencia) {
    this->frequencia = frequencia;
}

// Inicio incrementar frequencia de um No
void HashNo::incrementarFrequencia() {
    this->frequencia++;
}
// Fim incrementar frequencia de um No

string HashNo::getAppVersion() {
    return this->app_version;
}

void HashNo::setAppVersion(string app_version) {
    this->app_version = app_version;
}

HashNo *HashNo::getProximo() {
    return this->proximo;
}

void HashNo::setProximo(HashNo *proximo) {
    this->proximo = proximo;
}
// Fim Getters e Setters
