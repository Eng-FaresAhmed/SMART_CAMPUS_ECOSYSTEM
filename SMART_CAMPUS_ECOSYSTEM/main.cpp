#include <iostream>
#include <vector>

#include "LabHardware.h"
#include "CafeteriaItem.h"
#include "BookstoreMedia.h"

#include "CashPayment.h"
#include "CardPayment.h"

using namespace std;

int main() {

    vector<Resource*> resources;

    resources.push_back(
        new LabHardware(1, "Dell Laptop", 50000, 5, 24)
    );

    resources.push_back(
        new CafeteriaItem(2, "Burger", 120, 20, "10/6/2026")
    );

    resources.push_back(
        new BookstoreMedia(3, "C++ Book", 350, 10, "Bjarne")
    );

    cout << "===== Resources =====" << endl;

    for (Resource* r : resources) {
        r->display();
        cout << endl;
    }

    cout << "===== Purchase Test =====" << endl;

    try {

        resources[0]->purchase(10);

    }
    catch (const exception& e) {

        cout << "Error: " << e.what() << endl;
    }

    cout << endl;

    cout << "===== Payment Test =====" << endl;

    try {

        CardPayment card("123");
        card.pay(500);

    }
    catch (const exception& e) {

        cout << "Error: " << e.what() << endl;
    }

    for (Resource* r : resources) {
        delete r;
    }

    return 0;
}