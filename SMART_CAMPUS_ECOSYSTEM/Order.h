#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "OrderItem.h"
#include "User.h"

using namespace std;

class Order {
private:
    User* user;
    vector<OrderItem> items;
    string deliveryType;

    static const double DELIVERY_SURCHARGE;

public:
    Order(User* user, string deliveryType);

    void addItem(Resource* resource, int quantity);

    double getSubtotal() const;
    double getDiscountAmount() const;
    double getDeliveryCharge() const;
    double getTotal() const;

    void display() const;
    //
    string getSummary() const;

};
