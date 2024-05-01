#include <iostream>
#include "Pixel.h"
using namespace std;

Pixel::Pixel(unsigned char b, unsigned char g, unsigned char r) {
        blue = b;
        green = g;
        red = r;
    }

unsigned char Pixel::getColor(int index) const {
    if (index == 0) {
        return blue;
    } else if (index == 1) {
        return green;
    } else if (index == 2) {
        return red;
    }
    return 0;
}
