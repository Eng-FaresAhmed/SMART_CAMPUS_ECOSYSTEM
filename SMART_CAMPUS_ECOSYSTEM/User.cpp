#include "User.h"

User::User(string name, string campusID) {
    this->name = name;
    this->campusID = campusID;
}

string User::getName() const {
    return name;
}

string User::getCampusID() const {
    return campusID;
}

void User::display() const {
    cout << "Name: " << name << endl;
    cout << "Campus ID: " << campusID << endl;
    cout << "Role: " << getRole() << endl;
}

User::~User() {
}
