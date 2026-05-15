#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>

#include "Resource.h"
#include "LabHardware.h"
#include "CafeteriaItem.h"
#include "BookstoreMedia.h"
#include "Order.h"

using namespace std;

class FileManager {
public:
    // Save all resources to file
    static void saveResources(const vector<Resource*>& resources, const string& filename = "resources.txt");

    // Load all resources from file
    static void loadResources(vector<Resource*>& resources, const string& filename = "resources.txt");

    // Append order summary to transactions file
    static void saveOrder(const Order& order, const string& filename = "transactions.txt");
};
