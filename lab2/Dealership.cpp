//
// Created by aarit on 12/23/2023.
//

#include "Dealership.h"
Dealership::Dealership(std::string name, unsigned int capacity) {
    dealerName = name;
    fullCapacity = capacity;
}
void Dealership::AddShowroom(Showroom s) {
    if (numberOfShowrooms == fullCapacity) {
        cout << "Dealership is full, can't add another showroom!" << endl;
    } else {
        showroom.push_back(s);
        numberOfShowrooms += 1;
    }
}
float Dealership::GetAveragePrice() {
    for (int w = 0; w < showroom.size(); w++) {
        numberOfCars += showroom[w].GetVehicleList().size();
        for (int p = 0; p < showroom[w].GetVehicleList().size(); p++) {
            cars = showroom[w].GetVehicleList();
            total += cars[p].GetPrice();
        }
    }
    average = total/numberOfCars;
    return average;
}
void Dealership::ShowInventory() {
    if (showroom.size() == 0) {
        cout << dealerName << " is empty!" << endl << "Average car price: $0.00";
    } else {
        for (int f = 0; f < showroom.size(); f++) {
            cout << "Vehicles in " << showroom[f].showName << endl;
            cars = showroom[f].GetVehicleList();
            for (int j = 0; j < cars.size(); j++ ) {
                cars[j].Display();
            }
            cout << endl;
        }
        specificAverage = GetAveragePrice();
        cout << "Average car price: $" << specificAverage;
    }
}