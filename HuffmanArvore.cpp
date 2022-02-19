#include "HuffmanArvore.h"

HuffmanArvore::HuffmanArvore(long tamanhoOriginal) {
    this->codigosHuffman = new bool*[TAMANHO_MAXIMO];
    this->tamanhosHuffman = new int[TAMANHO_MAXIMO];
    this->tamanhoComprimido = 0;
    this->tamanhoOriginal = tamanhoOriginal;
    this->raiz = nullptr;
    this->minHeap = nullptr;
}

HuffmanArvore::~HuffmanArvore() {
    delete this->minHeap;
}

HuffmanHeap* HuffmanArvore::criarEconstruirMinHeap(char *dados, int *frequencia, long tamanho) {
    HuffmanHeap *minHeap = new HuffmanHeap(tamanho);

    for (int i = 0; i < tamanho; ++i) {
        minHeap->setNoArrayNos(new HuffmanNo(dados[i], frequencia[i]), i);
    }

    minHeap->setTamanho(tamanho);
    minHeap->buildMinHeap();

    return minHeap;
}

HuffmanNo* HuffmanArvore::construirHuffmanArvore(char *dados, int *frequencia, long tamanho) {
    HuffmanNo *left, *right, *top;

    HuffmanHeap *minHeap = criarEconstruirMinHeap(dados, frequencia, tamanho);
    this->minHeap = minHeap;

    while (!minHeap->isSizeOne()) {
        left = minHeap->extractMin();
        right = minHeap->extractMin();

        top = new HuffmanNo('$', left->getFrequencia() + right->getFrequencia());

        top->setEsquerda(left);
        top->setDireita(right);

        minHeap->insertMinHeap(top);
    }

    return minHeap->extractMin();
}

void HuffmanArvore::codificar(char *dados, int *frequencia, long tamanho) {
    HuffmanNo *root = construirHuffmanArvore(dados, frequencia, tamanho);
    this->raiz = root;

    //int arr[TAMANHO_MAXIMO], top = 0;
    int arr[this->minHeap->getCapacidade()], top = 0;

    salvarCodigos(root, arr, top);
//    imprimirCodificado(root, arr, top);
}

void HuffmanArvore::salvarCodigos(HuffmanNo* root, int arr[], int top) {
    if (root->getEsquerda()) {
        arr[top] = 0;
        salvarCodigos(root->getEsquerda(), arr, top + 1);
    }
    if (root->getDireita()) {
        arr[top] = 1;
        salvarCodigos(root->getDireita(), arr, top + 1);
    }
    if (root->ehFolha()) {
        int char_int = root->getDado() + METADE_MAXIMO;
        this->codigosHuffman[char_int] = new bool[top];
        this->tamanhosHuffman[char_int] = top;
        this->salvarArray(arr, top, this->codigosHuffman[char_int]);
    }
}

void HuffmanArvore::imprimirCodificado(HuffmanNo* root, int arr[], int top) {
    if (root->getEsquerda()) {
        arr[top] = 0;
        imprimirCodificado(root->getEsquerda(), arr, top + 1);
    }
    if (root->getDireita()) {
        arr[top] = 1;
        imprimirCodificado(root->getDireita(), arr, top + 1);
    }
    if (root->ehFolha()) {
        cout<< root->getDado() << ": ";
        imprimirArray(arr, top);
    }
}

void HuffmanArvore::salvarArray(int *arr, int n, bool* codigo) {
    int i;

    for (i = 0; i < n; ++i)
        codigo[i] = arr[i];
}

void HuffmanArvore::imprimirArray(int *arr, int n) {
    int i;

    for (i = 0; i < n; ++i)
        cout<< arr[i];

    cout<<"\n";
}

void HuffmanArvore::salvarTamanhos(char *letras, int *frequencias) {
    this->tamanhoComprimido = 1;
    for(int i = 0; i < minHeap->getCapacidade(); i++) {
        int char_int = letras[i] + METADE_MAXIMO;
        this->tamanhoComprimido += (this->tamanhosHuffman[char_int] * frequencias[i]);
    }
}

bool* HuffmanArvore::comprimirHuffman(char *letras, int *frequencias, string reviews_texts) {
    this->salvarTamanhos(letras, frequencias);

    bool* stringComprimida = new bool[(int)this->tamanhoComprimido];
    int charAtual = 0;

    for(int i = 0; i < this->tamanhoOriginal; i++){
        int char_int = reviews_texts[i] + METADE_MAXIMO;
        for(int j = 0; j < this->tamanhosHuffman[char_int]; j++) {
            stringComprimida[charAtual] = this->codigosHuffman[char_int][j];
            charAtual++;
        }
    }

    return stringComprimida;
}

long HuffmanArvore::getTamanhoComprimido() {
    return this->tamanhoComprimido;
}

string HuffmanArvore::descomprimirHuffman(bool *comprimido) {
    HuffmanNo* noAtual = this->raiz;

    string descomprimido = "";

    for (int i = 0; i < ((int)this->tamanhoComprimido); i++) {
        if (noAtual->ehFolha()) {
            descomprimido += noAtual->getDado();
            noAtual = this->raiz;
        }
        if (comprimido[i]){
            noAtual = noAtual->getDireita();
        }else{
            noAtual = noAtual->getEsquerda();
        }
    }

    return descomprimido + ' ';
}
