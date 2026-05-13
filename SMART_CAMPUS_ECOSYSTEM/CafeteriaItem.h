#pragma once
#include "Resource.h"

class CafeteriaItem : public Resource {
private:
    string expiryDate;

public:
    CafeteriaItem(int id, string name, double price, int stock, string expiryDate);

    void display() const override;
    string getCategory() const override;
    double operationalCost() const override;
};