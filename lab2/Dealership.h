//
// Created by aarit on 12/23/2023.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include "Vehicle.h"
#include "Showroom.h"
using namespace std;
class Dealership {
public:
    string dealerName;
    unsigned int fullCapacity = 0;
    int numberOfShowrooms = 0;
    float total = 0;
    vector <Showroom> showroom;
    vector <Vehicle> cars;
    float numberOfCars = 0;
    float average = 0;
    float specificAverage = 0;
    Dealership(string name = "Generic Dealership", unsigned int capacity = 0);
    void AddShowroom(Showroom s);
    float GetAveragePrice();
    void ShowInventory();
};



