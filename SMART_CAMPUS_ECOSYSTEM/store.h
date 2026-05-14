#pragma once
#include "Resource.h"

#include <iostream>
#include <vector>
using namespace std;


class Store {
private:
    string storeName;

    
    vector<Resource*> items;

public:
    Store(string name);
    void addItem(Resource* item);
    void displayAll() const;
    int getCount() const;
    Resource* findByID(int id) const;

    vector<Resource*> filterByCategory(const string& category) const;

    ~Store();
};