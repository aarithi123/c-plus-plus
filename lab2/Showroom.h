//
// Created by aarit on 12/22/2023.
//
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include "Vehicle.h"
using namespace std;




class Showroom {
public:
    string showName;
    vector<Vehicle> vehicle;
    unsigned int maxCapacity = 0;
    unsigned int numberOfVehicles = 0;

    Showroom(string name = "Unnamed Showroom", unsigned int capacity = 0);
    vector<Vehicle> GetVehicleList();
    void AddVehicle(Vehicle v);
    void ShowInventory();
    float GetInventoryValue();

};



