#pragma once
#include "User.h"

class Staff : public User {
public:
    Staff(string name, string campusID);

    string getRole() const override;
    double getDiscount() const override;
};
