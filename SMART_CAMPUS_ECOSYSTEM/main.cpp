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

// Template function: search for a resource by ID in any vector
template <typename T>
T* findByID(vector<T*>& items, int id) {
    for (T* item : items) {
        if (item->getId() == id)
            return item;
    }
    return nullptr;
}

int main() {
    vector<Resource*> resources;

    //
    FileManager::loadResources(resources);


    if (resources.empty()) {
        cout << "Error: Could not load resources. Exiting." << endl;
        return 0;
    }
        // Aggregation: Store holds pointers to resources, does NOT own them
        Store campusStore("Smart Campus Store");
        {
        for (Resource* r : resources) {
            campusStore.addItem(r);
        }

        StockMonitor monitor(resources, 3, 20);
        monitor.start();



        vector<string> validStaffIDs = { "S001", "S002", "S003", "S004", "S005" };

        cout << "===== User Registration =====" << endl;
        cout << "Note: Staff IDs must be pre-registered (e.g. S001), Student IDs start with 'ST'" << endl;

        string name, campusID;
        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Enter your Campus ID: ";
        getline(cin, campusID);

        User* user = nullptr;
        bool isStaff = false;

        auto it = find(validStaffIDs.begin(), validStaffIDs.end(), campusID);  //  it : algorithm library
        if (it != validStaffIDs.end()) {
            user = new Staff(name, campusID);
            isStaff = true;
        }
        else {
            user = new Student(name, campusID);
        }
       

        user->display();
        cout << endl;

        string menuChoice;

        while (true) {
            cout << "\n===== Smart Campus Menu =====" << endl;
            cout << "1. Search Resource by ID" << endl;
            cout << "2. Compare Two Resources Cost" << endl;
            cout << "3. Place Order" << endl;
            cout << "4. Browse Store" << endl;
            if (isStaff) {
                cout << "5. Restock Resource" << endl;
                cout << "6. Exit" << endl;
            }
            else {
                cout << "5. Exit" << endl;
            }
            cout << "Choose: ";
            getline(cin, menuChoice);

            if (menuChoice == "1") {
                cout << "Enter Resource ID to search: ";
                int searchID;
                cin >> searchID;
				cin.ignore(); //  Ignore leftover newline from previous input

                // Template findByID applied on Store's items (Aggregation + Template)
                vector<Resource*> storeItems = campusStore.getItems();
                Resource* found = findByID(storeItems, searchID);

                if (found == nullptr) {
                    cout << "Resource not found." << endl;
                }
                else {
                    cout << "===== Resource Report =====" << endl;
                    cout << *found << endl;                                   // COUT OPERTOR
                    cout << "==========================" << endl;
                }
            }
            else if (menuChoice == "2") {
                cout << "Enter first Resource ID: ";
                int id1;
                cin >> id1;
                cout << "Enter second Resource ID: ";
                int id2;
                cin >> id2;
                cin.ignore(); 

                vector<Resource*> storeItems = campusStore.getItems();
                Resource* r1 = findByID(storeItems, id1);
                Resource* r2 = findByID(storeItems, id2);

                if (r1 == nullptr || r2 == nullptr) {
                    cout << "One or both Resources not found." << endl;
                }
                else {
                    cout << "===== Cost Comparison =====" << endl;
                    cout << r1->getName() << " operational cost: " << r1->operationalCost() << " EGP" << endl;
                    cout << r2->getName() << " operational cost: " << r2->operationalCost() << " EGP" << endl;

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

                    vector<Resource*> storeItems = campusStore.getItems();
                    Resource* found = findByID(storeItems, resID);

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

                    cout << endl << "===== Payment =====" << endl;
                    cout << "Choose payment method (1 = Cash, 2 = Card): ";
                    string payChoice;
                    getline(cin, payChoice);

                    bool paymentSuccess = false;

                    try {
                        if (payChoice == "2") {
                            cout << "Enter 16-digit card number: ";
                            string cardNum;
                            getline(cin, cardNum);
                            CardPayment card(cardNum);
                            card.pay(order.getTotal());
                            paymentSuccess = true;
                        }
                        else {
                            CashPayment cash;
                            cash.pay(order.getTotal());
                            paymentSuccess = true;
                        }
                    }
                    catch (const exception& e) {
                        cout << "Payment Error: " << e.what() << endl;
                    }

                    if (paymentSuccess) {
                        FileManager::saveResources(resources);
                        FileManager::saveOrder(order);
                    }
                }
                catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
            }
            else if (menuChoice == "4") {
                // Aggregation
                campusStore.displayAll();
                cout << "Total items in store: " << campusStore.getCount() << endl;
            }
            else if (menuChoice == "5" && isStaff) {
                cout << "Enter Resource ID to restock: ";
                int restockID;
                cin >> restockID;
                cout << "Enter quantity to add: ";
                int restockQty;
                cin >> restockQty;
                cin.ignore();

                vector<Resource*> storeItems = campusStore.getItems();
                Resource* found = findByID(storeItems, restockID);

                if (found == nullptr)
                    cout << "Resource not found." << endl;
                else {
                    found->restock(restockQty);
                    cout << found->getName() << " restocked. New stock: " << found->getStock() << endl;
                    FileManager::saveResources(resources);
                }
            }
            else if ((menuChoice == "5" && !isStaff) || (menuChoice == "6" && isStaff)) {
                cout << "Goodbye!" << endl;
                break;
            }
            else {
                cout << "Invalid choice. Please try again." << endl;
            }
        }

        monitor.stop();

        delete user;
        for (Resource* r : resources) delete r;

        return 0;
    }
}