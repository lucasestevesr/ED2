#include <iostream>
#include <fstream>
#include "Review.h"
#include "Arquivo.h"
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

// Inicio Salvar Review
void Review::salvarReview(ofstream &arquivo_bin, ofstream &arquivo_posicoes) {
    int posicaoReview = arquivo_bin.tellp();
    Arquivo::salvarString(arquivo_bin, this->id);
    Arquivo::salvarString(arquivo_bin, this->text);
    arquivo_bin.write((char *) &this->upvotes, sizeof(int));
    Arquivo::salvarString(arquivo_bin, this->app_version);
    Arquivo::salvarString(arquivo_bin, this->posted_date);
    arquivo_posicoes.write((char *) &posicaoReview, sizeof(int));
}
// Fim Salvar Review