#pragma once
#include "Resource.h"

class BookstoreMedia : public Resource {
private:
    string author;

public:
    BookstoreMedia(int id, string name, double price, int stock, string author);

    void display() const override;
    string getCategory() const override;
    double operationalCost() const override;
};