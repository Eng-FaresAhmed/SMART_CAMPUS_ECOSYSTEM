#include "CafeteriaItem.h"

CafeteriaItem::CafeteriaItem(int id, string name, double price, int stock, string expiryDate)
    : Resource(id, name, price, stock) {

    this->expiryDate = expiryDate;
}

void CafeteriaItem::display() const {
    cout << *this;
    cout << "Expiry Date: " << expiryDate << endl;
}

string CafeteriaItem::getCategory() const {
    return "Cafeteria Item";
}

double CafeteriaItem::operationalCost() const {
    return price * 0.15;
}
//
string CafeteriaItem::getExpiryDate() const {
    return expiryDate;
}
