#include "StockMonitor.h"

StockMonitor::StockMonitor(vector<Resource*>& resources, int threshold, int intervalSeconds)
    : resources(resources), threshold(threshold), intervalSeconds(intervalSeconds), running(false) {
}

void StockMonitor::monitor() {
    while (running) {
        for (Resource* r : resources) {
            if (r->getStock() <= threshold) {
                cout << "\n[STOCK ALERT] \"" << r->getName()
                    << "\" is low on stock! Only " << r->getStock()
                    << " left.\n" << endl;
            }
        }
        this_thread::sleep_for(chrono::seconds(intervalSeconds));
    }
}

void StockMonitor::start() {
    running = true;
    monitorThread = thread(&StockMonitor::monitor, this);
    cout << "[StockMonitor] Started — checking every " << intervalSeconds << " seconds." << endl;
}

void StockMonitor::stop() {
    running = false;
    if (monitorThread.joinable()) {
        monitorThread.join();
    }
    cout << "[StockMonitor] Stopped." << endl;
}

StockMonitor::~StockMonitor() {
    stop();
}