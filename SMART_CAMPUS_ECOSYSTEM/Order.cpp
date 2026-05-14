#include "Order.h"
#include <exception>

class EmptyOrderException : public exception {
public:
    const char* what() const noexcept override {
        return "Order has no items!";
    }
};

const double Order::DELIVERY_SURCHARGE = 25.0;

Order::Order(User* user, string deliveryType) {
    this->user = user;
    this->deliveryType = deliveryType;
}

void Order::addItem(Resource* resource, int quantity) {

    try {
        resource->purchase(quantity);
        items.push_back(OrderItem(resource, quantity));
    }
    catch (const exception& e) {
        cout << "Could not add \"" << resource->getName() << "\": " << e.what() << endl;
    }
}

double Order::getSubtotal() const {

    double subtotal = 0.0;

    for (const OrderItem& item : items) {
        subtotal += item.getSubtotal();
    }

    return subtotal;
}

double Order::getDiscountAmount() const {
    return getSubtotal() * user->getDiscount();
}

double Order::getDeliveryCharge() const {

    if (deliveryType == "Delivery") {
        return DELIVERY_SURCHARGE;
    }

    return 0.0;
}

double Order::getTotal() const {
    return getSubtotal() - getDiscountAmount() + getDeliveryCharge();
}

void Order::display() const {

    if (items.empty()) {
        throw EmptyOrderException();
    }

    cout << "===== Order Summary =====" << endl;
    cout << "User: " << user->getName() << " (" << user->getRole() << ")" << endl;
    cout << "Campus ID: " << user->getCampusID() << endl;
    cout << "Delivery: " << deliveryType << endl;
    cout << "Items:" << endl;

    for (const OrderItem& item : items) {
        item.display();
    }

    cout << "Subtotal:  " << getSubtotal() << " EGP" << endl;

    if (user->getDiscount() > 0.0) {
        cout << "Discount (" << (user->getDiscount() * 100) << "%): -"
             << getDiscountAmount() << " EGP" << endl;
    }

    if (getDeliveryCharge() > 0.0) {
        cout << "Delivery Surcharge: " << getDeliveryCharge() << " EGP" << endl;
    }

    cout << "Total:     " << getTotal() << " EGP" << endl;
    cout << "=========================" << endl;
}
// 
string Order::getSummary() const {
    string s = "";
    s += "User: " + user->getName() + "\n";
    s += "Delivery: " + deliveryType + "\n";
    s += "Total: " + to_string(getTotal()) + "\n";
    return s;
}
