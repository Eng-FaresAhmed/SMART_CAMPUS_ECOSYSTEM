#pragma once
#include "User.h"

class Student : public User {
public:
    Student(string name, string campusID);

    string getRole() const override;
    double getDiscount() const override;
};
