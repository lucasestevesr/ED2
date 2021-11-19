#include <iostream>
#include <fstream>
#include "Review.h"

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
    int contador = 1;
    Review *review = new Review();
//    arquivo_processado.read(reinterpret_cast<char *>(review), sizeof(Review));
    while(arquivo_processado.read((char *)review, sizeof(Review))) {
        if(contador == id) {
            return review;
        }
        contador++;
    }
    return nullptr;
}

