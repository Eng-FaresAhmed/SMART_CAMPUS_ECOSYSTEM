#include "Staff.h"

Staff::Staff(string name, string campusID) : User(name, campusID) {
}

string Staff::getRole() const {
    return "Staff";
}

double Staff::getDiscount() const {
    return 0.10;
}
