#include "Store.h"
#include "Resource.h"

Store::Store(string name) : storeName(name) {}

void Store::addItem(Resource* item) {
    items.push_back(item);
}

void Store::displayAll() const {
    cout << "===== Store: " << storeName << " =====" << endl;
    if (items.empty()) {
        cout << "No items available." << endl;
        return;
    }
    for (Resource* item : items) {
        item->display();
        cout << endl;
    }
}

int Store::getCount() const {
    return items.size();
}


vector<Resource*> Store::getItems() const {
    return items;
}

// Aggregation: does NOT delete — main() owns the resources
Store::~Store() {
    items.clear();
}
