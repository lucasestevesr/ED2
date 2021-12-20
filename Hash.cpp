#include "Hash.h"
#include "Ordenar.h"

// Construtor
Hash::Hash(int tamanho) {
    // Seta o tamanho
    this->tamanho = tamanho;
    // Cria vetor de ponteiro de lista encadeada com o tamanho
    this->hashEncadeado = new HashEncadeadoPonteiro[tamanho];
    // Para cada posicao do array aloca uma nova lista
    for(int i = 0; i < tamanho; i++) {
        this->hashEncadeado[i] = new HashEncadeado();
    }
}
// Fim Construtor

// Destrutor
Hash::~Hash() {
    // Percorre toda a tabela
    for(int i = 0; i < tamanho; i++) {
        // Desaloca a lista escadeada de cada posicao
        delete this->hashEncadeado[i];
    }
    // Deleta a lista inteira de ponteiros
    delete [] this->hashEncadeado;
}
// Fim Destrutor

// Inicio Getters e Setters
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
// Fim Getters e Setters

// Inicio funcao da formula do hash para retorna a chave
int Hash::getChave(string app_version) {
    unsigned long hash = 5381; // hash inicial
    // Percorre cada caractere da string
    for (int i = 0; i < app_version.size(); i++) {
        // aplica a formula do algoritmo djb2
        hash = 33 * hash + (unsigned char)app_version[i];
    }
    // Retorna o hash mod tamanho para garantir que a posicao existe
    return hash % this->tamanho;
}
// Fim funcao da formula do hash para retorna a chave

// Inicio inserir string na tabela Hash
void Hash::inserir(string app_version) {
    // Verifica se a string é diferente de vazia
    if(!app_version.empty()) {
        // Pega a chave da formula com base na string
        int chave = Hash::getChave(app_version);

        // Busca um no na lista encadeada da chave com o mesmo valor de string
        HashNo *hashNo = this->hashEncadeado[chave]->buscarHashNo(app_version);

        if(hashNo != nullptr) {
            // Se achar incrementa a frequencia dele
            hashNo->incrementarFrequencia();
        } else {
            // Se não achar insere ele na lista encadeada da chave
            this->hashEncadeado[chave]->inserir(app_version);
        }
    }
}
// Fim inserir string na tabela Hash

// Inicio imprimir tabela hash
void Hash::imprimir() {
    // Percorre todas posicoes da tabela
    for (int i = 0; i < this->tamanho; i++) {
        // Se na posicao atual tem uma lista que nao é vazia entra pra imprimir a lista
        if(!this->hashEncadeado[i]->vazia()) {
            // Imprime a posicao da tabela e depois a lista encadeada contida nesta posicao
            cout << "Posicao i = " << i << endl;
            this->hashEncadeado[i]->imprimir();
        }
    }
}
// Fim imprimir tabela hash

// Inicio ordenar e imprimir tabela Hash ordenada
void Hash::imprimirOrdenado(int qnt) {
    // Recupera a quantidade de nos tem somando todas listas encadeadas da tabela
    // ou seja, quantas posicoes string tem na tabela
    int tamanhoVetor = Hash::recuperarQuantidadeNos();
    // Criar o vetor auxiliar pra armazenar a frequencia
    int *vetorFrequencia = Hash::transformarVetorFrequencia(tamanhoVetor);
    // Criar o vetor auxiliar pra armazenar a string app version
    string *vetorAppVersion = Hash::transformarVetorAppVersion(tamanhoVetor);
    // Ordena os dois vetores juntos vinculados por indices iguais usando quicksort
    Ordenar::quickSortHash(vetorFrequencia, vetorAppVersion, 0, tamanhoVetor-1);
    int qntAtual = 0; // variavel auxiliar
    for (int i = tamanhoVetor-1; i > 0; i--) {
        // Imprime a versao e sua frequencia
        cout << "Versao: " << vetorAppVersion[i] << endl;
        cout << "Frequencia: " << vetorFrequencia[i] << endl;
        // Incrementa a variavel auxiliar
        qntAtual++;
        // Se ja exibiu a quantidade necessaria da break no loop
        if(qntAtual == qnt) {
            break;
        }
    }
    // Desaloca memoria dos dois vetores auxiliares usados
    delete [] vetorFrequencia;
    delete [] vetorAppVersion;
}
// Fim ordenar e imprimir tabela Hash ordenada

// Inicio ordenar e escrever tabela Hash ordenada em arquivo
void Hash::imprimirArquivo(ofstream &arquivo_testes) {
    // Recupera a quantidade de nos tem somando todas listas encadeadas da tabela
    // ou seja, quantas posicoes string tem na tabela
    int tamanhoVetor = Hash::recuperarQuantidadeNos();
    // Criar o vetor auxiliar pra armazenar a frequencia
    int *vetorFrequencia = Hash::transformarVetorFrequencia(tamanhoVetor);
    // Criar o vetor auxiliar pra armazenar a string app version
    string *vetorAppVersion = Hash::transformarVetorAppVersion(tamanhoVetor);
    // Ordena os dois vetores juntos vinculados por indices iguais usando quicksort
    Ordenar::quickSortHash(vetorFrequencia, vetorAppVersion, 0, tamanhoVetor-1);
    for (int i = tamanhoVetor-1; i > 0; i--) {
        // Escreve a versao e a frequencia no arquivo de teste
        arquivo_testes << "Versao: " << vetorAppVersion[i] << endl;
        arquivo_testes << "Frequencia: " << vetorFrequencia[i] << endl;
    }
    // Desaloca memoria dos dois vetores auxiliares usados
    delete [] vetorFrequencia;
    delete [] vetorAppVersion;
}
// Fim ordenar e escrever tabela Hash ordenada em arquivo

// Inicio recuperar quantidade de Nos tem na tabela
int Hash::recuperarQuantidadeNos() {
    // Tamanho comeca como 0
    int tamanho = 0;
    // Percorre todas posicoes da tabela hash
    for (int i = 0; i < this->tamanho; i++) {
        // Se na posicao atual tem uma lista nao vazia é porque tem string nela
        if (!this->hashEncadeado[i]->vazia()) {
            // Incrementa o tamanho da tabela hash, ou seja, a quantidade de nos
            tamanho += this->hashEncadeado[i]->getTamanho();
        }
    }
    // Retorna o tamanho da tabela hash
    return tamanho;
}
// Fim recuperar quantidade de Nos tem na tabela

// Inicio criar vetor de frequencias com todos valores da tabela
int* Hash::transformarVetorFrequencia(int tamanho) {
    // Posicao do vetor iniciada como 0
    int posicao = 0;
    // Aloca as posicoes do vetor
    int *vetorFrequencias = new int[tamanho];
    // Percorre a tabela hash
    for (int i = 0; i < this->tamanho; i++) {
        // Se na posicao atual não for uma lista encadeada vazia
        if (!this->hashEncadeado[i]->vazia()) {
            // percorre toda a lista encadeada
            for(HashNo *noAtual = this->hashEncadeado[i]->getInicio(); noAtual != nullptr; noAtual = noAtual->getProximo()) {
                // Salva a frequencia no vetor
                vetorFrequencias[posicao] = noAtual->getFrequencia();
                // Incrementa a posicao do vetor
                posicao++;
            }
        }
    }
    // Retorna o vetor frequencia
    return vetorFrequencias;
}
// Fim criar vetor de frequencias com todos valores da tabela

// Inicio criar vetor de strings de app version da tabela
string* Hash::transformarVetorAppVersion(int tamanho) {
    // Posicao do vetor iniciada como 0
    int posicao = 0;
    // Aloca as posicoes do vetor
    string *vetorAppVersion = new string[tamanho];
    // Percorre a tabela hash
    for (int i = 0; i < this->tamanho; i++) {
        // Se na posicao atual não for uma lista encadeada vazia
        if (!this->hashEncadeado[i]->vazia()) {
            // percorre toda a lista encadeada
            for(HashNo *noAtual = this->hashEncadeado[i]->getInicio(); noAtual != nullptr; noAtual = noAtual->getProximo()) {
                // Salva o app version no vetor
                vetorAppVersion[posicao] = noAtual->getAppVersion();
                // Incrementa a posicao do vetor
                posicao++;
            }
        }
    }
    // Retorna o vetor app versions
    return vetorAppVersion;
}
// Fim criar vetor de strings de app version da tabela