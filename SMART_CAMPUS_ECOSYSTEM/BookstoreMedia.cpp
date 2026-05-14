#include "BookstoreMedia.h"

BookstoreMedia::BookstoreMedia(int id, string name, double price, int stock, string author)
    : Resource(id, name, price, stock) {

    this->author = author;
}

void BookstoreMedia::display() const {
    cout << *this;
    cout << "Author: " << author << endl;
}

string BookstoreMedia::getCategory() const {
    return "Bookstore Media";
}

double BookstoreMedia::operationalCost() const {
    return price * 0.10;
}
//
string BookstoreMedia::getAuthor() const { return author; }
