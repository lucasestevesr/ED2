#include "Hash.h"
#include "Ordenar.h"

Hash::Hash(int tamanho) {
    this->tamanho = tamanho;
    this->hashEncadeado = new HashEncadeadoPonteiro[tamanho];
    for(int i = 0; i < tamanho; i++) {
        this->hashEncadeado[i] = new HashEncadeado();
    }
}

Hash::~Hash() {
    for(int i = 0; i < tamanho; i++) {
        delete this->hashEncadeado[i];
    }
    delete [] this->hashEncadeado;
}

int Hash::getTamanho() {
    return this->tamanho;
}

void Hash::setTamanho(int tamanho) {
    this->tamanho = tamanho;
}

HashEncadeadoPonteiro* Hash::getHashEncadeado() {
    return this->hashEncadeado;
}

void Hash::setHashEncadeado(HashEncadeadoPonteiro *hashEncadeado) {
    this->hashEncadeado = hashEncadeado;
}

int Hash::getChave(string app_version) {
    unsigned long hash = 5381;
    for (int i = 0; i < app_version.size(); i++) {
        hash = 33 * hash + (unsigned char)app_version[i];
    }
    return hash % this->tamanho;
}

void Hash::inserir(string app_version) {
    if(!app_version.empty()) {
        int chave = Hash::getChave(app_version);

        HashNo *hashNo = this->hashEncadeado[chave]->buscarHashNo(app_version);

        if(hashNo != nullptr) {
            hashNo->incrementarFrequencia();
        } else {
            this->hashEncadeado[chave]->inserir(app_version);
        }
    }
}

void Hash::imprimir() {
    for (int i = 0; i < this->tamanho; i++) {
        if(!this->hashEncadeado[i]->vazia()) {
            cout << "Posicao i = " << i << endl;
            this->hashEncadeado[i]->imprimir();
        }
    }
}

void Hash::imprimirOrdenado(int qnt) {
    int tamanhoVetor = Hash::recuperarQuantidadeNos();
    int *vetorFrequencia = Hash::transformarVetorFrequencia(tamanhoVetor);
    string *vetorAppVersion = Hash::transformarVetorAppVersion(tamanhoVetor);
    Ordenar::quickSortHash(vetorFrequencia, vetorAppVersion, 0, tamanhoVetor-1);
    int qntAtual = 0;
    for (int i = tamanhoVetor-1; i > 0; i--) {
        cout << "Versao: " << vetorAppVersion[i] << endl;
        cout << "Frequencia: " << vetorFrequencia[i] << endl;
        qntAtual++;
        if(qntAtual == qnt) {
            break;
        }
    }
    delete [] vetorFrequencia;
    delete [] vetorAppVersion;
}

int Hash::recuperarQuantidadeNos() {
    int tamanho = 0;
    for (int i = 0; i < this->tamanho; i++) {
        if (!this->hashEncadeado[i]->vazia()) {
            tamanho += this->hashEncadeado[i]->getTamanho();
        }
    }
    return tamanho;
}

int* Hash::transformarVetorFrequencia(int tamanho) {
    int posicao = 0;
    int *vetorFrequencias = new int[tamanho];
    for (int i = 0; i < this->tamanho; i++) {
        if (!this->hashEncadeado[i]->vazia()) {
            for(HashNo *noAtual = this->hashEncadeado[i]->getInicio(); noAtual != nullptr; noAtual = noAtual->getProximo()) {
                vetorFrequencias[posicao] = noAtual->getFrequencia();
                posicao++;
            }
        }
    }
    return vetorFrequencias;
}

string* Hash::transformarVetorAppVersion(int tamanho) {
    int posicao = 0;
    string *vetorAppVersion = new string[tamanho];
    for (int i = 0; i < this->tamanho; i++) {
        if (!this->hashEncadeado[i]->vazia()) {
            for(HashNo *noAtual = this->hashEncadeado[i]->getInicio(); noAtual != nullptr; noAtual = noAtual->getProximo()) {
                vetorAppVersion[posicao] = noAtual->getAppVersion();
                posicao++;
            }
        }
    }
    return vetorAppVersion;
}