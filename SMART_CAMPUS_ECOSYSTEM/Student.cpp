#include "Student.h"

Student::Student(string name, string campusID) : User(name, campusID) {
}

string Student::getRole() const {
    return "Student";
}

double Student::getDiscount() const {
    return 0.0;
}
