#pragma once
#include "Resource.h"

class LabHardware : public Resource {
private:
    int warrantyMonths;

public:
    LabHardware(int id, string name, double price, int stock, int warrantyMonths);

    void display() const override;
    string getCategory() const override;
    double operationalCost() const override;
    //
    int getWarrantyMonths() const;

};