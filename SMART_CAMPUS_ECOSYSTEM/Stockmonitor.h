#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include "Resource.h"

using namespace std;

class StockMonitor {
private:
    vector<Resource*>& resources;
    int threshold;              
    int intervalSeconds;         
    atomic<bool> running;        
    thread monitorThread;

    void monitor();             

public:
    StockMonitor(vector<Resource*>& resources, int threshold = 3, int intervalSeconds = 5);

    void start();
    void stop();

    ~StockMonitor();
};