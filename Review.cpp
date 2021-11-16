#include "Review.h"

Review::Review(string id, string text, int upvotes, string app_version, string posted_date) {
    this->id = id;
    this->text = text;
    this->upvotes = upvotes;
    this->app_version = app_version;
    this->posted_date = posted_date;
}

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