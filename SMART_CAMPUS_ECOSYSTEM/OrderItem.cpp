#include "OrderItem.h"

OrderItem::OrderItem(Resource* resource, int quantity) {
    this->resource = resource;
    this->quantity = quantity;
}

Resource* OrderItem::getResource() const {
    return resource;
}

int OrderItem::getQuantity() const {
    return quantity;
}

double OrderItem::getSubtotal() const {
    return resource->getPrice() * quantity;
}

void OrderItem::display() const {
    cout << "  - " << resource->getName()
         << " x" << quantity
         << " = " << getSubtotal() << " EGP" << endl;
}
