#include "HashEncadeado.h"

// Construtor
HashEncadeado::HashEncadeado() {
    this->inicio = nullptr;
    this->tamanho = 0;
}
// Fim Construtor

// Destrutor
HashEncadeado::~HashEncadeado() {
    // Percorre lista enquanto o inicio for diferente de null
    while(this->inicio != nullptr) {
        // Se o proximo ao inicio tambem for diferente de null
        if(inicio->getProximo() != nullptr) {
            // Pega o proximo do inicio como No temporario
            HashNo *temp = inicio->getProximo();
            // Seta o proximo do inicio como null para evitar erro de lixo de memoria
            this->inicio->setProximo(nullptr);
            // Deleta o no inicio
            delete this->inicio;
            // Inicio recebe o antigo proximo dele, o temporario
            // Dessa forma vai removendo 1 por 1 do inicio até desalocar toda a lista
            this->inicio = temp;
        } else {
            // Inicio recebe null
            this->inicio = nullptr;
        }
    }
}
// Fim Destrutor

// Inicio Getters e setters
HashNo* HashEncadeado::getInicio() {
    return inicio;
}

void HashEncadeado::setInicio(HashNo *inicio) {
    this->inicio = inicio;
}

int HashEncadeado::getTamanho() {
    return tamanho;
}

void HashEncadeado::setTamanho(int tamanho) {
    this->tamanho = tamanho;
}
// Fim Getters e setters

// Inicio verificar lista vazia
bool HashEncadeado::vazia() {
    return this->inicio == nullptr;
}
// Fim verificar lista vazia

// Inicio inserir no inicio da lista
void HashEncadeado::inserir(string app_version) {
    // Verifica se a lista nao é vazia
    if(!app_version.empty()) {
        // Cria um novo No
        HashNo *no = new HashNo(app_version, 1);
        // Seta o proximo como o inicio atual da lista
        no->setProximo(this->inicio);
        // Inicio da lista recebe o novo No
        this->inicio = no;
        // Incrementa o tamanho da lista encadeada
        this->tamanho++;
    }
}
// Fim inserir no inicio da lista

// Inicio buscar No pela app version
HashNo* HashEncadeado::buscarHashNo(string app_version) {
    // Se a string app version nao for vazia
    if(!app_version.empty()) {
        // Percorre toda lista encadeada
        for (HashNo *noAtual = this->inicio; noAtual != nullptr; noAtual = noAtual->getProximo()) {
            // Compara o no atual com a string app version
            if (noAtual->getAppVersion() == app_version) {
                // Retorna o No se achar
                return noAtual;
            }
        }
    }
    // Se nao achar nada retorna ponteiro para null
    return nullptr;
}
// Fim buscar No pela app version

// Inicio imprimir lista encadeada
void HashEncadeado::imprimir() {
    // Percorre toda lista encadeada e escreve ela
    for (HashNo *noAtual = this->inicio; noAtual != nullptr; noAtual = noAtual->getProximo()) {
        cout << "App Version: " << noAtual->getAppVersion() << endl;
        cout << "Frequencia Colisao: " << noAtual->getFrequencia() << endl;
    }
}
// Fim imprimir lista encadeada