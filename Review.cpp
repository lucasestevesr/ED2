#include <iostream>
#include <fstream>
#include "Review.h"
#include <chrono>

using namespace std;

Review::Review(string id, string text, int upvotes, string app_version, string posted_date) {
    this->id = id;
    this->text = text;
    this->upvotes = upvotes;
    this->app_version = app_version;
    this->posted_date = posted_date;
}

Review::Review() {};

Review::~Review() {};

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

void Review::imprimir() {
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << this->id << endl;
    cout << this->text << endl;
    cout << this->upvotes << endl;
    cout << this->app_version << endl;
    cout << this->posted_date << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
}

void Review::salvarString(ofstream &arquivo_bin, string valor) {
    size_t tamanho = valor.size();
    arquivo_bin.write((char *) &tamanho, sizeof(tamanho));
    arquivo_bin.write(valor.c_str(), tamanho);
}

void Review::salvarReview(ofstream &arquivo_bin) {
    salvarString(arquivo_bin, this->id);
    salvarString(arquivo_bin, this->text);
    arquivo_bin.write((char *) &this->upvotes, sizeof(int));
    salvarString(arquivo_bin, this->app_version);
    salvarString(arquivo_bin, this->posted_date);
}

int Review::recuperarQuantidadeReviews(ifstream &arquivo_processado) {
    int quantidade = 0;
    int posicao = sizeof(int) * -1;
    arquivo_processado.clear();
    arquivo_processado.seekg(posicao, arquivo_processado.end);
    arquivo_processado.read((char *) &quantidade, sizeof(int));

    return quantidade;
}

string Review::recuperarString(ifstream &arquivo_processado) {
    string texto;
    string::size_type tamanho;
    arquivo_processado.read((char *) &tamanho, sizeof(tamanho));
    texto.resize(tamanho);
    arquivo_processado.read(&texto[0], tamanho);

    return texto;
}

Review* Review::recuperarReviewPeloId(ifstream &arquivo_processado, int id) {
    int intAux;
    int idAtual = 1;
    Review *review = new Review();
    int total = Review::recuperarQuantidadeReviews(arquivo_processado);

    arquivo_processado.clear();
    arquivo_processado.seekg(0, arquivo_processado.beg);

    while (arquivo_processado.good()) {
        review->setId(Review::recuperarString(arquivo_processado));
        review->setText(Review::recuperarString(arquivo_processado));
        arquivo_processado.read((char *) &intAux, sizeof(int));
        review->setUpvotes(intAux);
        review->setAppVersion(Review::recuperarString(arquivo_processado));
        review->setPostedDate(Review::recuperarString(arquivo_processado));

        if (idAtual == id) {
            return review;
        }
        if(idAtual >= total) {
            break;
        }

        idAtual++;
    }

    return nullptr;
}

