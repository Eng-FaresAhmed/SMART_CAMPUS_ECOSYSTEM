#include "Resource.h"
#include <exception>

class InsufficientStock : public exception {
public:

    const char* what() const noexcept override {
        return "Insufficient stock!";
    }
};

Resource::Resource(int id, string name, double price, int stock) {

    this->id = id;
    this->name = name;
    this->price = price;
    this->stock = stock;
}

void Resource::restock(int amount) {
    stock += amount;
}

void Resource::purchase(int quantity) {

    if (quantity > stock) {
        throw InsufficientStock();
    }

    stock -= quantity;
}

int Resource::getId() const {
    return id;
}

string Resource::getName() const {
    return name;
}

double Resource::getPrice() const {
    return price;
}

int Resource::getStock() const {
    return stock;
}

bool Resource::operator>(const Resource& other) const {
    return operationalCost() > other.operationalCost();
}

ostream& operator<<(ostream& out, const Resource& r) {

    out << "ID: " << r.id << endl;
    out << "Name: " << r.name << endl;
    out << "Category: " << r.getCategory() << endl;
    out << "Price: " << r.price << endl;
    out << "Stock: " << r.stock << endl;

    return out;
}

Resource::~Resource() {
}