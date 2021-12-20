#include "HashNo.h"

HashNo::HashNo(string app_version, int frequencia) {
    this->app_version = app_version;
    this->frequencia = frequencia;
}

HashNo::HashNo() {}

HashNo::~HashNo() {
    this->app_version.clear();
}

int HashNo::getFrequencia() {
    return this->frequencia;
}

void HashNo::setFrequencia(int frequencia) {
    this->frequencia = frequencia;
}

void HashNo::incrementarFrequencia() {
    this->frequencia++;
}

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
