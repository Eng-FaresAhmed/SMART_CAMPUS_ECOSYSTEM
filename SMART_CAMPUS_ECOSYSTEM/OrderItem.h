#pragma once
#include "Resource.h"

class OrderItem {
private:
    Resource* resource;
    int quantity;

public:
    OrderItem(Resource* resource, int quantity);

    Resource* getResource() const;
    int getQuantity() const;
    double getSubtotal() const;

    void display() const;
};
