//
// Created by aarit on 12/22/2023.
//
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include "Vehicle.h"
using namespace std;

Vehicle::Vehicle() {
    make = "COP3503";
    model = "Rust Bucket";
    year = 1900;
    price = 0;
    mileage = 0;

}
Vehicle::Vehicle(string make1, string model1, int year1, float price1, int mileage1) {
    make = make1;
    model = model1;
    year = year1;
    price = price1;
    mileage = mileage1;
}

void Vehicle::Display() {
    cout << make << " " << model << " " << year << " $" << price << " " << mileage << endl;
}


string Vehicle::GetYearMakeModel() {
    string YearMakeModel;
    string x = to_string(year);
    YearMakeModel = x + " " + make + " " + model;
    return YearMakeModel;
}

float Vehicle::GetPrice() {
    return price;
}


