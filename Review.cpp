#include "Review.h"
#include <iostream>

using namespace std;

Review::Review(int id, int text, int upvotes, int app_version, int posted_date) {
    this->id = id;
    this->text = text;
    this->upvotes = upvotes;
    this->app_version = app_version;
    this->posted_date = posted_date;
}

Review::~Review() {};

int Review::getId() {
    return this->id;
}

void Review::setId(int id) {
    this->id = id;
}

int Review::getText() {
    return this->text;
}

void Review::setText(int text) {
    this->text = text;
}

int Review::getUpvotes() {
    return this->upvotes;
}

void Review::setUpvotes(int upvotes) {
    this->upvotes = upvotes;
}

int Review::getAppVersion() {
    return this->app_version;
}

void Review::setAppVersion(int app_version) {
    this->app_version = app_version;
}

int Review::getPostedDate() {
    return this->posted_date;
}

void Review::setPostedDate(int posted_date) {
    this->posted_date = posted_date;
}