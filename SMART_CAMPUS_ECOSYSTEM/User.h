#pragma once
#include <iostream>
#include <string>

using namespace std;

class User {
protected:
    string name;
    string campusID;

public:
    User(string name, string campusID);

    virtual string getRole() const = 0;
    virtual double getDiscount() const = 0;

    string getName() const;
    string getCampusID() const;

    virtual void display() const;

    virtual ~User();
};
