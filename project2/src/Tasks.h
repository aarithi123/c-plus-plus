#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "Pixel.h"
#include "Image.h"
using namespace std;

class Tasks {
private:
    Image::Header header;
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    //fstream myFile;
public:
    Image readFile(string fileName);
    bool writeFile(string fileName, Image &image);
    vector<Image> onlyColor(Image &image);
    Image flip(Image &image);
    Image multiply(Image &image1, Image &image2);
    float normalized(unsigned char org, unsigned char max, unsigned char min);
    Image subtract(Image &image1, Image &image2);
    //Image screen(Image &image1, Image &image2, Image &image3);
    Image screen(Image &image1, Image &image2);
    Image overlay(Image &image1, Image &image2);
    Image scale(Image &image, bool value1, float blueScale, bool value2, float greenScale, bool value3, float redScale);
    Image combine(Image &image1, Image &image2, Image &image3);
    //Image addColor(Image &image, char _blue, char _green, char _red);
    Image addColor(Image &image, int _blue, int _green, int _red);
};