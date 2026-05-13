#pragma once
#include <iostream>

using namespace std;

class Payment {
public:
    virtual void pay(double amount) = 0;

    virtual ~Payment();
};