//
// Created by aarit on 12/22/2023.
//
#include <iostream>
#include <string>
#include <vector>
#include "Showroom.h"

using namespace std;

Showroom::Showroom(string name, unsigned int capacity) {
    showName = name;
    maxCapacity = capacity;
}

void Showroom::AddVehicle(Vehicle v) {
    if (numberOfVehicles == maxCapacity) {
        cout << "Showroom is full! Cannot add " << v.GetYearMakeModel() << endl;
    }else {
        vehicle.push_back(v);
        numberOfVehicles += 1;
    }
}

void Showroom::ShowInventory() {
    if (numberOfVehicles == 0) {
        cout << "Unnamed Showroom is empty!" << endl;
    } else {
        cout << "Vehicles in " << showName << endl;
        for (int s = 0; s < vehicle.size(); s++) {
            vehicle[s].Display();
        }
    }
}

float Showroom::GetInventoryValue() {
    float total = 0;
    for (int j = 0; j < vehicle.size(); j ++) {
        total += vehicle[j].GetPrice();

    }

    return total;
}

vector<Vehicle> Showroom::GetVehicleList() {
    return vehicle;
}