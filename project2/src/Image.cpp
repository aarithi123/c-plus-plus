#include <iostream>
#include <vector>
#include "Image.h"
using namespace std;

Image::Image() {
    header.idLength = 0;
    width = 0;
    height = 0;
}
Image::Image(Image::Header h) {
    header = h;
    height = h.height;
    width = h.width;
}
Image::Header Image::getHeader() {
    return header;
}
short Image::getHeight() {
    return height;
}
short Image::getWidth() {
    return width;
}
Pixel Image::getPixel(int index) {
    return pixels[index];
}
int Image::getPixelCount() {
    return height*width;
}
void Image::addPixel(Pixel &P) {
    pixels.push_back(P);
}
