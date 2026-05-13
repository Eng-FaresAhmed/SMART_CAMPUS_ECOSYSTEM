#include <iostream>
#include <vector>

#include "LabHardware.h"
#include "CafeteriaItem.h"
#include "BookstoreMedia.h"

#include "CashPayment.h"
#include "CardPayment.h"

#include "Student.h"
#include "Staff.h"
#include "Order.h"

using namespace std;

int main() {

    vector<Resource*> resources;

    resources.push_back(new LabHardware(1, "Dell Laptop", 50000, 5, 24));
    resources.push_back(new CafeteriaItem(2, "Burger", 120, 20, "10/6/2026"));
    resources.push_back(new BookstoreMedia(3, "C++ Book", 350, 10, "Bjarne"));

    cout << "===== Available Resources =====" << endl;
    for (Resource* r : resources) {
        r->display();
        cout << endl;
    }

    cout << "===== User Registration =====" << endl;

    string name, campusID, roleChoice;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter your Campus ID: ";
    getline(cin, campusID);

    cout << "Are you a Student or Staff? (1 = Student, 2 = Staff): ";
    getline(cin, roleChoice);

    User* user = nullptr;

    if (roleChoice == "1") {
        user = new Student(name, campusID);
    } else {
        user = new Staff(name, campusID);
    }

    user->display();
    cout << endl;

    string deliveryChoice;
    cout << "Choose delivery type (1 = Pickup, 2 = Dorm Delivery): ";
    getline(cin, deliveryChoice);

    string deliveryType = (deliveryChoice == "2") ? "Delivery" : "Pickup";

    Order order(user, deliveryType);

    cout << endl << "===== Add Items to Order =====" << endl;

    string addMore = "y";

    while (addMore == "y" || addMore == "Y") {

        cout << "Enter Resource ID to add: ";
        int resID;
        cin >> resID;

        cout << "Enter quantity: ";
        int qty;
        cin >> qty;
        cin.ignore();

        Resource* found = nullptr;
        for (Resource* r : resources) {
            if (r->getId() == resID) {
                found = r;
                break;
            }
        }

        if (found == nullptr) {
            cout << "Resource ID not found." << endl;
        } else {
            order.addItem(found, qty);
        }

        cout << "Add another item? (y/n): ";
        getline(cin, addMore);
    }

    cout << endl;
    try {
        order.display();
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << endl << "===== Payment =====" << endl;
    cout << "Choose payment method (1 = Cash, 2 = Card): ";
    string payChoice;
    getline(cin, payChoice);

    try {
        if (payChoice == "2") {
            cout << "Enter 16-digit card number: ";
            string cardNum;
            getline(cin, cardNum);
            CardPayment card(cardNum);
            card.pay(order.getTotal());
        } else {
            CashPayment cash;
            cash.pay(order.getTotal());
        }
    }
    catch (const exception& e) {
        cout << "Payment Error: " << e.what() << endl;
    }

    delete user;
    for (Resource* r : resources) {
        delete r;
    }

    return 0;
}
