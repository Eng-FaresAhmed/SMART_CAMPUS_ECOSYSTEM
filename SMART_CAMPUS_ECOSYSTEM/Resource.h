#pragma once
#include <iostream>
#include <string>

using namespace std;

class Resource {
protected:
    int id;
    string name;
    double price;
    int stock;

public:
    Resource(int id, string name, double price, int stock);

    virtual void display() const = 0;
    virtual string getCategory() const = 0;
    virtual double operationalCost() const = 0;

    void restock(int amount);
    void purchase(int quantity);

    int getId() const;
    string getName() const;
    double getPrice() const;
    int getStock() const;

    bool operator>(const Resource& other) const;

    friend ostream& operator<<(ostream& out, const Resource& r);

    virtual ~Resource();
};