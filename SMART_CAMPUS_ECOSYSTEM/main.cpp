#include <iostream>
#include <vector>
#include <algorithm>
#include "LabHardware.h"
#include "CafeteriaItem.h"
#include "BookstoreMedia.h"
#include "CashPayment.h"
#include "CardPayment.h"
#include "Student.h"
#include "Staff.h"
#include "Order.h"
#include "FileManager.h"
#include "StockMonitor.h"
#include "Store.h"
using namespace std;

// Template function: returns the cheapest resource in a vector
template <typename T>
T* findMin(vector<T*>& items) {
    T* minItem = items[0];
    for (T* item : items) {
        if (item->getPrice() < minItem->getPrice())
            minItem = item;
    }
    return minItem;
}

int main() {
    vector<Resource*> resources;

    // Load previously saved resources from file
    FileManager::loadResources(resources);

    if (resources.empty()) {
        resources.push_back(new LabHardware(1, "Dell Laptop", 50000, 5, 24));
        resources.push_back(new CafeteriaItem(2, "Burger", 120, 20, "10/6/2026"));
        resources.push_back(new BookstoreMedia(3, "C++ Book", 350, 10, "Bjarne"));
    }

    StockMonitor monitor(resources, 3, 20);
    monitor.start();

    // Display all available resources to the user
    cout << "===== Available Resources =====" << endl;
    for (Resource* r : resources) {
        r->display();
        cout << endl;
    }

    // Template function usage: find cheapest resource
    Resource* cheapest = findMin(resources);
    cout << "Cheapest Resource: " << cheapest->getName() << " (" << cheapest->getPrice() << " EGP)" << endl << endl;

    // Aggregation: Store holds references to all resources
    Store campusStore("Smart Campus Store");
    for (Resource* r : resources) {
        campusStore.addItem(r);
    }

    // Pre-registered Staff IDs ? only these IDs are recognized as Staff
    vector<string> validStaffIDs = { "S001", "S002", "S003", "S004", "S005" };

    // User registration section
    cout << "===== User Registration =====" << endl;
    cout << "Note: Staff IDs must be pre-registered (e.g. S001), Student IDs start with 'ST'" << endl;

    string name, campusID;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter your Campus ID: ";
    getline(cin, campusID);

    User* user = nullptr;
    bool isStaff = false;

    // Check if the entered ID exists in the valid staff list
    auto it = find(validStaffIDs.begin(), validStaffIDs.end(), campusID);

    if (it != validStaffIDs.end()) {
        user = new Staff(name, campusID);
        isStaff = true;
        cout << "Role detected: Staff" << endl;
    }
    else if (campusID.size() >= 2 && campusID[0] == 'S' && campusID[1] == 'T') {
        user = new Student(name, campusID);
        cout << "Role detected: Student" << endl;
    }
    else {
        cout << "Invalid Campus ID format. Defaulting to Student." << endl;
        user = new Student(name, campusID);
    }

    user->display();
    cout << endl;

    string menuChoice;

    // Main menu loop
    while (true) {
        cout << "\n===== Smart Campus Menu =====" << endl;
        cout << "1. Search Resource by ID" << endl;
        cout << "2. Compare Two Resources Cost" << endl;
        cout << "3. Place Order" << endl;
        if (isStaff) {
            // Restock option is only shown to Staff
            cout << "4. Restock Resource" << endl;
            cout << "5. Exit" << endl;
        }
        else {
            cout << "4. Exit" << endl;
        }
        cout << "Choose: ";
        getline(cin, menuChoice);

        if (menuChoice == "1") {
            // Search using Store::findByID (Aggregation in action)
            cout << "Enter Resource ID to search: ";
            int searchID;
            cin >> searchID;
            cin.ignore();

            Resource* found = campusStore.findByID(searchID);

            if (found == nullptr) {
                cout << "Resource not found." << endl;
            }
            else {
                // Display detailed report of the found resource
                cout << "===== Resource Report =====" << endl;
                cout << "Name:     " << found->getName() << endl;
                cout << "Price:    " << found->getPrice() << " EGP" << endl;
                cout << "Category: " << found->getCategory() << endl;
                cout << "Stock:    " << found->getStock() << endl;
                cout << "==========================" << endl;
            }
        }
        else if (menuChoice == "2") {
            // Compare operational cost between two resources
            cout << "Enter first Resource ID: ";
            int id1;
            cin >> id1;

            cout << "Enter second Resource ID: ";
            int id2;
            cin >> id2;
            cin.ignore();

            Resource* r1 = nullptr;
            Resource* r2 = nullptr;

            for (Resource* r : resources) {
                if (r->getId() == id1) r1 = r;
                if (r->getId() == id2) r2 = r;
            }

            if (r1 == nullptr || r2 == nullptr) {
                cout << "One or both Resources not found." << endl;
            }
            else {
                cout << "===== Cost Comparison =====" << endl;
                cout << r1->getName() << " operational cost: " << r1->operationalCost() << " EGP" << endl;
                cout << r2->getName() << " operational cost: " << r2->operationalCost() << " EGP" << endl;

                // Use overloaded operator> to compare costs
                if (*r1 > *r2)
                    cout << r1->getName() << " has a higher operational cost." << endl;
                else if (*r2 > *r1)
                    cout << r2->getName() << " has a higher operational cost." << endl;
                else
                    cout << "Both have equal operational cost." << endl;
                cout << "===========================" << endl;
            }
        }
        else if (menuChoice == "3") {
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

                if (found == nullptr)
                    cout << "Resource ID not found." << endl;
                else
                    order.addItem(found, qty);

                cout << "Add another item? (y/n): ";
                getline(cin, addMore);
            }

            cout << endl;

            try {
                order.display();

                // Payment section
                cout << endl << "===== Payment =====" << endl;
                cout << "Choose payment method (1 = Cash, 2 = Card): ";
                string payChoice;
                getline(cin, payChoice);

                bool paymentSuccess = false;

                try {
                    if (payChoice == "2") {
                        // Card payment ? requires 16-digit card number
                        cout << "Enter 16-digit card number: ";
                        string cardNum;
                        getline(cin, cardNum);
                        CardPayment card(cardNum);
                        card.pay(order.getTotal());
                        paymentSuccess = true;
                    }
                    else {
                        // Default to cash payment
                        CashPayment cash;
                        cash.pay(order.getTotal());
                        paymentSuccess = true;
                    }
                }
                catch (const exception& e) {
                    cout << "Payment Error: " << e.what() << endl;
                }

                // Save updated stock and order details only if payment succeeded
                if (paymentSuccess) {
                    FileManager::saveResources(resources);
                    FileManager::saveOrder(order);
                }
            }
            catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (menuChoice == "4" && isStaff) {
            cout << "Enter Resource ID to restock: ";
            int restockID;
            cin >> restockID;

            cout << "Enter quantity to add: ";
            int restockQty;
            cin >> restockQty;
            cin.ignore();

            Resource* found = nullptr;
            for (Resource* r : resources) {
                if (r->getId() == restockID) {
                    found = r;
                    break;
                }
            }

            if (found == nullptr)
                cout << "Resource not found." << endl;
            else {
                found->restock(restockQty);
                cout << found->getName() << " restocked. New stock: " << found->getStock() << endl;
                FileManager::saveResources(resources);
            }
        }
        else if ((menuChoice == "4" && !isStaff) || (menuChoice == "5" && isStaff)) {
            // Exit the program
            cout << "Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    // Stop the stock monitor thread
    monitor.stop();

    // Free allocated memory
    delete user;
    for (Resource* r : resources) delete r;

    return 0;
}