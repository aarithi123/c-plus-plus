#pragma once
//
// Created by aarit on 12/22/2023.
//
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;


class Vehicle {
public:
    Vehicle();
    Vehicle(string make1, string model1, int year1, float price1, int mileage1);
    void Display();
    string GetYearMakeModel();
    float GetPrice();

private:
    string make;
    string model;
    unsigned int year;
    float price;
    unsigned int mileage;
};



