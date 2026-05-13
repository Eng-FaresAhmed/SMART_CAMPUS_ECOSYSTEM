#include "LabHardware.h"

LabHardware::LabHardware(int id, string name, double price, int stock, int warrantyMonths)
    : Resource(id, name, price, stock) {

    this->warrantyMonths = warrantyMonths;
}

void LabHardware::display() const {
    cout << *this;
    cout << "Warranty: " << warrantyMonths << " months" << endl;
}

string LabHardware::getCategory() const {
    return "Lab Hardware";
}

double LabHardware::operationalCost() const {
    return price * 0.25;
}