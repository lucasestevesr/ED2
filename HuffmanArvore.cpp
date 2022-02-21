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

// Funcao responsavel por criar a minHeap
HuffmanHeap* HuffmanArvore::criarEconstruirMinHeap(char *dados, long *frequencia, long tamanho, int *comparacoes) {
    
    // Inicializando a capacidade da heap igual ao tamanho passado
    HuffmanHeap *minHeap = new HuffmanHeap(tamanho);

    // Atribuindo a heap os elementos com suas respectivas frequencias
    for (int i = 0; i < tamanho; ++i) {
        minHeap->setNoArrayNos(new HuffmanNo(dados[i], frequencia[i]), i);
    }

    // definindo o tamanho da Heap
    minHeap->setTamanho(tamanho);
    // construindo a heap
    minHeap->buildMinHeap(comparacoes);

    return minHeap;
}

// Funcao responsavel por construir a Arvore de Huffman 

HuffmanNo* HuffmanArvore::construirHuffmanArvore(char *dados, long *frequencia, long tamanho, int *comparacoes) {
    
    // Ponteiro para raiz, para esquerda e direita (todos do mesmo tipo)
    HuffmanNo *left, *right, *top;

    // instanciando uma minHeap com os vetores de dados, frequencia e tamanho
    HuffmanHeap *minHeap = criarEconstruirMinHeap(dados, frequencia, tamanho, comparacoes);
    
    // fazendo atribuicao para a minHeap definida como atributo da arvore
    this->minHeap = minHeap;

    // iterando enquanto a heap não possuir exatamente 1 elemento
    while (!minHeap->isSizeOne()) {

        // extraindo dois elementos de frequencia minima
        left = minHeap->extractMin(comparacoes);
        right = minHeap->extractMin(comparacoes);

        // Criando um novo nó como a soma da frequencia dos dois nos anteriores
        top = new HuffmanNo('$', left->getFrequencia() + right->getFrequencia());

        // fazendo os dois nos como filhos esquerdo e direito da nova raiz
        top->setEsquerda(left);
        top->setDireita(right);

        // adicionando o no a minHeap
        minHeap->insertMinHeap(top, comparacoes);
    }

    return minHeap->extractMin(comparacoes);
}

void HuffmanArvore::codificar(char *dados, long *frequencia, long tamanho, int *comparacoes) {
    HuffmanNo *root = construirHuffmanArvore(dados, frequencia, tamanho, comparacoes);
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

// Funcao responsavel por imprimir a codificacao de Huffman a partir da raiz da arvore
void HuffmanArvore::imprimirCodificado(HuffmanNo* root, int arr[], int top) {

    // Definindo 0 para o no da esquerda
    if (root->getEsquerda()) {
        arr[top] = 0;
        imprimirCodificado(root->getEsquerda(), arr, top + 1);
    }

    // Definindo 1 para o no da direita
    if (root->getDireita()) {
        arr[top] = 1;
        imprimirCodificado(root->getDireita(), arr, top + 1);
    }

    // Verifica se este no eh folha, caso seja
    // imprimir o caractere corresponde e seu codigo
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

void HuffmanArvore::salvarTamanhos(char *letras, long *frequencias) {
    this->tamanhoComprimido = 1;
    for(int i = 0; i < minHeap->getCapacidade(); i++) {
        if(frequencias[i] > 0) {
            int char_int = letras[i] + METADE_MAXIMO;
            this->tamanhoComprimido += (this->tamanhosHuffman[char_int] * frequencias[i]);
        }
    }
}

// Funcao responsavel por fazer a compressao de Huffman
bool* HuffmanArvore::comprimirHuffman(char *letras, long *frequencias, string reviews_texts) {
    this->salvarTamanhos(letras, frequencias);
    // recebe o tamanho de todos os campos review_texts concatenados no formato binario
    bool* stringComprimida = new bool[(int)this->tamanhoComprimido];

    int charAtual = 0;
    // percorre o array de elementos
    for(int i = 0; i < this->tamanhoOriginal; i++){
        int char_int = reviews_texts[i] + METADE_MAXIMO;
        for(int j = 0; j < this->tamanhosHuffman[char_int]; j++) {
            // atribuindo o codigo binario correspondente de cada caractere
            stringComprimida[charAtual] = this->codigosHuffman[char_int][j];
            charAtual++;
        }
    }

    return stringComprimida;
}

double HuffmanArvore::getTamanhoComprimido() {
    return this->tamanhoComprimido;
}

// Função responsavel por fazer a decodificacao de huffman
string HuffmanArvore::descomprimirHuffman(bool *comprimido) {
    
    // A execucao começa a partir da raiz da árvore
    HuffmanNo* noAtual = this->raiz;

    string descomprimido = "";

    // percorrendo toda o conteudo comprimido
    for (int i = 0; i < ((int)this->tamanhoComprimido); i++) {
        
        // se o no eh folha adicione-o ao retorno
        if (noAtual->ehFolha()) {
            descomprimido += noAtual->getDado();
            noAtual = this->raiz;
        }
        // verificando se o indice eh 1 mover para o nó a direta
        if (comprimido[i]){
            noAtual = noAtual->getDireita();
        } else{ // caso contrario mova para o nó a esquerda
            noAtual = noAtual->getEsquerda();
        }
    }


    // resultado
    return descomprimido + ' ';
}
