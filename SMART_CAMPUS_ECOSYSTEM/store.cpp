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

Resource* Store::findByID(int id) const {
    for (Resource* item : items) {
        if (item->getId() == id)
            return item;
    }
    return nullptr;
}

vector<Resource*> Store::filterByCategory(const string& category) const {
    vector<Resource*> result;
    for (Resource* item : items) {
        if (item->getCategory() == category)
            result.push_back(item);  
    }
    return result;
}


Store::~Store() {
    items.clear();  // just clears pointers, does NOT free memory
}Resource* Store::findByID(int id) const {
    for (Resource* item : items) {
        if (item->getId() == id)
            return item;
    }
    return nullptr;
}

Store::~Store() {
    items.clear();
}