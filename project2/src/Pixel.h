#pragma once
#include <iostream>
using namespace std;

class Pixel {
public:
    Pixel(unsigned char b, unsigned char g, unsigned char r);
    unsigned char getColor(int index) const;
private:
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};
