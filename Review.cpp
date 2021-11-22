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
void Review::salvarReview(ofstream &arquivo_bin) {
    salvarString(arquivo_bin, this->id);
    salvarString(arquivo_bin, this->text);
    arquivo_bin.write((char *) &this->upvotes, sizeof(int));
    salvarString(arquivo_bin, this->app_version);
    salvarString(arquivo_bin, this->posted_date);
}
// Fim Salvar todos atributos do Review

// Recuperar quantidade de Reviews dentro do arquivo
int Review::recuperarQuantidadeReviews(ifstream &arquivo_processado) {
    // Declara variavel quantidade de Reviews
    int quantidade = 0;
    // Declara variavel posicao com size of do tipo int -1
    int posicao = sizeof(int) * -1;
    // Limpa o arquivo e vai para posicao
    // A quantidade de Reviews no arquivo BIN esta salvo no final do arquivo
    arquivo_processado.clear();
    arquivo_processado.seekg(posicao, arquivo_processado.end);
    // Recupera e seta a quantidade total de Reviews
    arquivo_processado.read((char *) &quantidade, sizeof(int));

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
Review* Review::recuperarReviewPeloId(ifstream &arquivo_processado, int id) {
    // Declara variaveis auxiliares
    int intAux;
    int idAtual = 1;
    Review *review = new Review();

    // Recupera quantidade total de Reviews
    int total = Review::recuperarQuantidadeReviews(arquivo_processado);

    // Move o cursor para o início do arquivo
    arquivo_processado.clear();
    arquivo_processado.seekg(0, arquivo_processado.beg);

    // Enquanto o arquivo não lançar excessão continua lendo
    while (arquivo_processado.good()) {
        // Le e seta os atributos da Review
        review->setId(Review::recuperarString(arquivo_processado));
        review->setText(Review::recuperarString(arquivo_processado));
        arquivo_processado.read((char *) &intAux, sizeof(int));
        review->setUpvotes(intAux);
        review->setAppVersion(Review::recuperarString(arquivo_processado));
        review->setPostedDate(Review::recuperarString(arquivo_processado));

        // Se o id procurado for igual ao Id atual, retorna o review
        if (idAtual == id) {
            return review;
        }
        // Se o id Atual for maior ou igual ao total de reviews
        // Da um break e para de percorrer o arquivo pois chegou ao final
        if(idAtual >= total) {
            break;
        }

        // Incrementa o id Atual
        idAtual++;
    }

    return nullptr;
}
// Fim Recuperar Review pelo índice

