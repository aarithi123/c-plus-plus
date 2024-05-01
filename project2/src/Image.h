#pragma once
#include <iostream>
#include <vector>
#include "Pixel.h"
using namespace std;

class Image {
public:
    struct Header {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };

    Image();
    Image(Header h);
    short getHeight();
    short getWidth();
    Header getHeader();
    Pixel getPixel(int index);
    int getPixelCount();
    void addPixel(Pixel &P);

private:
    Header header;
    short width;
    short height;
    vector<Pixel> pixels;
};
