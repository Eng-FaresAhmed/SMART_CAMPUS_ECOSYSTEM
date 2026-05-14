#include "Filemanager.h"
#include "FileManager.h"

// SAVE RESOURCES 
void FileManager::saveResources(const vector<Resource*>& resources, const string& filename) {
    try {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Could not open file for writing: " + filename);
        }

        for (Resource* r : resources) {
            string category = r->getCategory();

            file << category << "|"
                << r->getId() << "|"
                << r->getName() << "|"
                << r->getPrice() << "|"
                << r->getStock() << "|";

            if (category == "Lab Hardware") {
                LabHardware* lh = dynamic_cast<LabHardware*>(r);
                file << lh->getWarrantyMonths();
            }
            else if (category == "Cafeteria Item") {
                CafeteriaItem* ci = dynamic_cast<CafeteriaItem*>(r);
                file << ci->getExpiryDate();
            }
            else if (category == "Bookstore Media") {
                BookstoreMedia* bm = dynamic_cast<BookstoreMedia*>(r);
                file << bm->getAuthor();
            }

            file << "\n";
        }

        file.close();
        cout << "[FileManager] Resources saved to " << filename << endl;
    }
    catch (const exception& e) {
        cout << "[FileManager] Save Error: " << e.what() << endl;
    }
}

//  LOAD RESOURCES 
void FileManager::loadResources(vector<Resource*>& resources, const string& filename) {
    try {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Could not open file for reading: " + filename);
        }

        for (Resource* r : resources) delete r;
        resources.clear();

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            vector<string> parts;
            string token;
            for (char c : line) {
                if (c == '|') {
                    parts.push_back(token);
                    token = "";
                }
                else {
                    token += c;
                }
            }
            parts.push_back(token);

            if (parts.size() < 6) continue;

            string category = parts[0];
            int    id = stoi(parts[1]);
            string name = parts[2];
            double price = stod(parts[3]);
            int    stock = stoi(parts[4]);
            string extra = parts[5];

            if (category == "Lab Hardware") {
                resources.push_back(new LabHardware(id, name, price, stock, stoi(extra)));
            }
            else if (category == "Cafeteria Item") {
                resources.push_back(new CafeteriaItem(id, name, price, stock, extra));
            }
            else if (category == "Bookstore Media") {
                resources.push_back(new BookstoreMedia(id, name, price, stock, extra));
            }
        }

        file.close();
        cout << "[FileManager] Resources loaded from " << filename << endl;
    }
    catch (const exception& e) {
        cout << "[FileManager] Load Error: " << e.what() << endl;
    }
}

//  SAVE ORDER 
void FileManager::saveOrder(const Order& order, const string& filename) {
    try {
        ofstream file(filename, ios::app); 
        if (!file.is_open()) {
            throw runtime_error("Could not open file for writing: " + filename);
        }

        file << "========== ORDER ==========\n";
        file << order.getSummary();
        file << "===========================\n\n";

        file.close();
        cout << "[FileManager] Order saved to " << filename << endl;
    }
    catch (const exception& e) {
        cout << "[FileManager] Save Order Error: " << e.what() << endl;
    }
}