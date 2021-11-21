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
    cout << this->id << endl;
    cout << this->text << endl;
    cout << this->upvotes << endl;
    cout << this->app_version << endl;
    cout << this->posted_date << endl;
    cout << "--------------------------------------------------------------------------" << endl;
}

Review* Review::recuperarReviewPeloId(ifstream &arquivo_processado, int id) {
    auto start = std::chrono::high_resolution_clock::now();
    arquivo_processado.clear();
    arquivo_processado.seekg(0, arquivo_processado.beg);
    int count = 1;
    Review *rev = new Review;
    string textAux;
    int idAux;
    while (arquivo_processado.good()) {
        string::size_type sz;
        if (!arquivo_processado.read(reinterpret_cast<char *>(&sz), sizeof(string::size_type)))
            break;
        textAux.resize(sz);
        arquivo_processado.read(&textAux[0], sz);
        rev->setId(textAux);

        string::size_type sz2;
        arquivo_processado.read(reinterpret_cast<char *>(&sz2), sizeof(string::size_type));
        textAux.resize(sz2);
        arquivo_processado.read(&textAux[0], sz2);
        rev->setText(textAux);

        arquivo_processado.read(reinterpret_cast<char *>(&idAux), sizeof(int));
        rev->setUpvotes(idAux);

        string::size_type sz3;
        arquivo_processado.read(reinterpret_cast<char *>(&sz3), sizeof(string::size_type));
        textAux.resize(sz3);
        arquivo_processado.read(&textAux[0], sz3);
        rev->setAppVersion(textAux);

        string::size_type sz4;
        arquivo_processado.read(reinterpret_cast<char *>(&sz4), sizeof(string::size_type));
        textAux.resize(sz4);
        arquivo_processado.read(&textAux[0], sz4);
        rev->setPostedDate(textAux);

        if (count == id) {
            auto end = std::chrono::high_resolution_clock::now();
            auto int_s = std::chrono::duration_cast<std::chrono::seconds>(end - start);
            cout << "O tempo de execucao para busca do Id escolhido foi de " << std::to_string(int_s.count()) << " segundos." << endl;
            return rev;
        }

        count++;
    }

    return nullptr;
}

