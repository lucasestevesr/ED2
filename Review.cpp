#include <iostream>
#include <fstream>
#include "Review.h"
#include <chrono>

using namespace std;

// Construtor com atributos
Review::Review(string id, string text, int upvotes, string app_version, string posted_date) {
    this->id = id;
    this->text = text;
    this->upvotes = upvotes;
    this->app_version = app_version;
    this->posted_date = posted_date;
}
// Fim Construtor com atributos

// Construtor vazio
Review::Review() {};

// Destrutor
Review::~Review() {};

// Getters e Setters
string Review::getId() {
    return this->id;
}

void Review::setId(string id) {
    this->id = id;
}

string Review::getText() {
    return this->text;
}

void Review::setText(string text) {
    this->text = text;
}

int Review::getUpvotes() {
    return this->upvotes;
}

void Review::setUpvotes(int upvotes) {
    this->upvotes = upvotes;
}

string Review::getAppVersion() {
    return this->app_version;
}

void Review::setAppVersion(string app_version) {
    this->app_version = app_version;
}

string Review::getPostedDate() {
    return this->posted_date;
}

void Review::setPostedDate(string posted_date) {
    this->posted_date = posted_date;
}
// Fim Getters e Setters

// Imprimir Review
void Review::imprimir() {
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << this->id << endl;
    cout << this->text << endl;
    cout << to_string(this->upvotes) << endl;
    cout << this->app_version << endl;
    cout << this->posted_date << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
}
// Fim Imprimir Review

// Inicio Receber Review
void Review::receberReview(Review* review) {
    this->id = review->id;
    this->text = review->text;
    this->upvotes = review->upvotes;
    this->app_version = review->app_version;
    this->posted_date = review->posted_date;
}
// Fim Receber Review

// Salvar atributos do tipo string
void Review::salvarString(ofstream &arquivo_bin, string valor) {
    // Pega o tamanho da string
    size_t tamanho = valor.size();
    // Escreve o tamanho da string no arquivo
    arquivo_bin.write((char *) &tamanho, sizeof(tamanho));
    // Escreve a string com o tamanho dela no arquivo
    arquivo_bin.write(valor.c_str(), tamanho);
}
// Fim Salvar atributos do tipo string

// Salvar todos atributos do Review
void Review::salvarReview(ofstream &arquivo_bin, ofstream &arquivo_posicoes) {
    int posicaoReview = arquivo_bin.tellp();
    salvarString(arquivo_bin, this->id);
    salvarString(arquivo_bin, this->text);
    arquivo_bin.write((char *) &this->upvotes, sizeof(int));
    salvarString(arquivo_bin, this->app_version);
    salvarString(arquivo_bin, this->posted_date);
    arquivo_posicoes.write((char *) &posicaoReview, sizeof(int));
}
// Fim Salvar todos atributos do Review

// Recuperar quantidade de Reviews dentro do arquivo
int Review::recuperarQuantidadeReviews(ifstream &posicoes_salvas) {
    // Declara variavel quantidade de Reviews
    int quantidade = 0;
    // Vai para o final do arquivo das posicoes
    posicoes_salvas.clear();
    posicoes_salvas.seekg(0, posicoes_salvas.end);
    // Pega a posicao do final
    int posicaoFinal = posicoes_salvas.tellg();
    // Divide pra saber quantos registros tem no binario
    quantidade = posicaoFinal / sizeof(int);

    return quantidade;
}
// Fim Recuperar quantidade de Reviews dentro do arquivo

// Recuperar atributos do tipo string
string Review::recuperarString(ifstream &arquivo_processado) {
    // Declara a variavel texto e a variavel tamanho
    string texto;
    string::size_type tamanho;
    // Le o tamanho da string no arquivo processado
    arquivo_processado.read((char *) &tamanho, sizeof(tamanho));
    // Le a string usando o tamanho lido
    texto.resize(tamanho);
    arquivo_processado.read(&texto[0], tamanho);

    return texto;
}
// Fim Recuperar atributos do tipo string

// Recuperar Review pelo índice
Review* Review::recuperarReviewPeloId(ifstream &arquivo_processado, ifstream &posicoes_salvas, int id) {
    // Declara variaveis auxiliares
    int intAux;
    int idAtual = 1;
    Review *review = new Review();

    // Recupera quantidade total de Reviews
    int total = Review::recuperarQuantidadeReviews(posicoes_salvas);

    // Verificando se existe o review salvo
    if(id <= 0 || id > total) {
        return nullptr;
    }

    // Pegando posicao salva do registro
    int posicao = Review::recuperarPosicaoReviewPeloId(posicoes_salvas, id);

    // Se a posicao for -1 o registro não existe
    if(posicao == -1) {
        return nullptr;
    }

    // Move o cursor para a posicao do review
    arquivo_processado.clear();
    arquivo_processado.seekg(posicao, arquivo_processado.beg);

    // Enquanto o arquivo não lançar excessão continua lendo
    while(arquivo_processado.good()) {
        // Le e seta os atributos da Review
        review->setId(Review::recuperarString(arquivo_processado));
        review->setText(Review::recuperarString(arquivo_processado));
        arquivo_processado.read((char *) &intAux, sizeof(int));
        review->setUpvotes(intAux);
        review->setAppVersion(Review::recuperarString(arquivo_processado));
        review->setPostedDate(Review::recuperarString(arquivo_processado));

        return review;
    }

    return nullptr;
}
// Fim Recuperar Review pelo índice

// Recuperar Posição Review pelo índice
int Review::recuperarPosicaoReviewPeloId(ifstream &posicoes_salvas, int id) {
    // Declara variaveis uteis de posicao
    int posicaoReview = -1;
    int posicaoCursor = (id - 1) * sizeof(int);

    // Move o cursor para o início do arquivo
    posicoes_salvas.clear();
    posicoes_salvas.seekg(posicaoCursor, posicoes_salvas.beg);

    // Le a posicao do review
    posicoes_salvas.read((char *) &posicaoReview, sizeof(int));

    return posicaoReview;
}
// Fim recuperar Posição Review pelo índice

