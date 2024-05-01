#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "Pixel.h"
#include "Image.h"
#include "Tasks.h"
using namespace std;

Image Tasks::readFile(string fileName) {
    ifstream myFile(fileName, ios_base::binary);

    //myFile.open(fileName, ios::in | ios::binary);
    if (myFile.is_open()) {
        myFile.read(&header.idLength, sizeof(header.idLength));
        myFile.read(&header.colorMapType, sizeof(header.colorMapType));
        myFile.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
        myFile.read((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        myFile.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
        myFile.read((char*)&header.colorMapDepth, sizeof(header.colorMapDepth));
        myFile.read((char*)&header.xOrigin, sizeof(header.xOrigin));
        myFile.read((char*)&header.yOrigin, sizeof(header.yOrigin));
        myFile.read((char*)&header.width,sizeof(header.width));
        myFile.read((char*)&header.height, sizeof(header.height));
        myFile.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        myFile.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

        Image image(header);
        for (int i = 0; i < header.height * header.width; i++) {
            myFile.read((char*)&blue,sizeof(blue));
            myFile.read((char*)&green, sizeof(green));
            myFile.read((char*)&red, sizeof(red));
            Pixel p = Pixel(blue, green, red);
            image.addPixel( p);
        }
        myFile.close();
        return image;
    } else {
        return Image();
    }

}

bool Tasks::writeFile(string fileName, Image &image) {
    int count = image.getPixelCount();
    header = image.getHeader();
    ofstream myFile(fileName, ios_base::binary);
    //myFile.open(fileName, ios::out | ios::binary);
    if(myFile.is_open()) {
        myFile.write((char *) &header.idLength, sizeof(header.idLength));
        myFile.write((char *) &header.colorMapType, sizeof(header.colorMapType));
        myFile.write((char *) &header.dataTypeCode, sizeof(header.dataTypeCode));
        myFile.write((char *) &header.colorMapOrigin, sizeof(header.colorMapOrigin));
        myFile.write((char *) &header.colorMapLength, sizeof(header.colorMapLength));
        myFile.write((char *) &header.colorMapDepth, sizeof(header.colorMapDepth));
        myFile.write((char *) &header.xOrigin, sizeof(header.xOrigin));
        myFile.write((char *) &header.yOrigin, sizeof(header.yOrigin));
        myFile.write((char *) &header.width, sizeof(header.width));
        myFile.write((char *) &header.height, sizeof(header.height));
        myFile.write((char *) &header.bitsPerPixel, sizeof(header.bitsPerPixel));
        myFile.write((char *) &header.imageDescriptor, sizeof(header.imageDescriptor));
        for (int i = 0; i < count; i++) {
            Pixel pixel = image.getPixel(i);
            blue = pixel.getColor(0);
            green = pixel.getColor(1);
            red = pixel.getColor(2);

            myFile.write((char *) &blue, sizeof(blue));
            myFile.write((char *) &green, sizeof(green));
            myFile.write((char *) &red, sizeof(red));
        }
        myFile.close();
        return true;
    } else {
        return false;
    }
}

vector<Image> Tasks::onlyColor(Image &image) {
    vector<Image> images;
    int count = image.getPixelCount();
    header = image.getHeader();
    Image blueImage(header);
    Image greenImage(header);
    Image redImage(header);

    for(int i = 0; i < count; i++) {
        Pixel pixel = image.getPixel(i);
        blue = pixel.getColor(0);
        green = pixel.getColor(1);
        red = pixel.getColor(2);
        Pixel bluePixel(blue, blue, blue);
        blueImage.addPixel(bluePixel);
        Pixel greenPixel(green, green, green);
        greenImage.addPixel(greenPixel);
        Pixel redPixel(red, red, red);
        redImage.addPixel(redPixel);
    }
    images.push_back(blueImage);
    images.push_back(greenImage);
    images.push_back(redImage);
    return images;
}

Image Tasks::flip(Image &image) {
    header = image.getHeader();
    Image newImage(header);
    int count = (image.getHeight() * image.getWidth()) - 1;
    for(int i = count; i > -1; i--) {
        Pixel pixel = image.getPixel(i);
        newImage.addPixel(pixel);
    }
    return newImage;
}

Image Tasks::multiply(Image &image1, Image &image2) {
    header = image1.getHeader();
    header = image1.getHeader();
    int count = image1.getPixelCount();
    Image newImage(header);
    float arr[6];
    unsigned char tmparr[3];
    for(int i = 0; i < count; i++) {
        Pixel pixel1 = image1.getPixel(i);
        Pixel pixel2 = image2.getPixel(i);
        for(int j = 0; j < 6; j++) {
            if (j < 3) {
                arr[j] = normalized(pixel1.getColor(j), (unsigned char)(255), (unsigned char)(0));
            } else {
                arr[j] = normalized(pixel2.getColor(j-3), (unsigned char)(255), (unsigned char)(0));
            }
        }

        for(int a = 0; a < 3; a++) {
            if(arr[a] * arr[a+3] > 1) {
                tmparr[a] = (unsigned char)(255);
            } else {
                tmparr[a] = (unsigned char)((arr[a] * arr[a+3]) * 255 + 0.5f);
            }
        }

        Pixel newPixel(tmparr[0], tmparr[1], tmparr[2]);
        newImage.addPixel(newPixel);
    }
    return newImage;
}

float Tasks::normalized(unsigned char org, unsigned char max, unsigned char min) {
    float normal = (float)(org) / (float)(max - min);
    return normal;
}

Image Tasks::subtract(Image &image2, Image &image1) {
    header = image1.getHeader();
    int count = image1.getPixelCount();
    Image newImage(header);
    unsigned char arr[6];
    unsigned char tmparr[3];
    for (int i = 0; i < count; i++) {
        Pixel pixel1 = image1.getPixel(i);
        Pixel pixel2 = image2.getPixel(i);
        for (int j = 0; j < 6; j++) {
            if (j < 3) {
                arr[j] = pixel1.getColor(j);
            } else {
                arr[j] = pixel2.getColor(j - 3);
            }
        }
        for (int a = 0; a < 3; a++) {
            if (arr[a + 3] - arr[a] >= 0) {
                tmparr[a] = (unsigned char)(arr[a + 3] - arr[a]);
            } else {
                tmparr[a] = (unsigned char)(0);
            }
        }

        Pixel newPixel(tmparr[0], tmparr[1], tmparr[2]);
        newImage.addPixel(newPixel);
    }

    return newImage;
}

/*
Image Tasks::screen(Image &image1, Image &image2, Image &image3) {
    Image temp = multiply(image1, image2);
    header = temp.getHeader();
    Image newImage(header);
    int count = image3.getPixelCount();
    float arr[6];
    unsigned char tmparr[3];
    for(int i = 0; i < count; i++) {
        Pixel pixel1 = image3.getPixel(i);
        Pixel pixel2 = temp.getPixel(i);
        for(int j = 0; j < 6; j++) {
            if (j < 3) {
                arr[j] = normalized(pixel1.getColor(j), (unsigned char)(255), (unsigned char)(0));
            } else {
                arr[j] = normalized(pixel2.getColor(j-3), (unsigned char)(255), (unsigned char)(0));
            }
        }
        for(int a = 0; a < 3; a++) {
            float num = 1 - (1 - arr[a]) * (1 - arr[a + 3]);
            if(num > 1) {
                num = 1;
            } else if (num < 0) {
                num = 0;
            }
            tmparr[a] = (unsigned char)(num * 255 + 0.5f);
        }
        Pixel newPixel(tmparr[0], tmparr[1], tmparr[2]);
        newImage.addPixel(newPixel);
    }
    return newImage;

}
*/

Image Tasks::screen(Image &image1, Image &image2) {
    header = image1.getHeader();
    header = image1.getHeader();
    int count = image1.getPixelCount();
    Image newImage(header);
    float arr[6];
    unsigned char tmparr[3];
    for(int i = 0; i < count; i++) {
        Pixel pixel1 = image1.getPixel(i);
        Pixel pixel2 = image2.getPixel(i);
        for(int j = 0; j < 6; j++) {
            if (j < 3) {
                arr[j] = normalized(pixel1.getColor(j), (unsigned char)(255), (unsigned char)(0));
            } else {
                arr[j] = normalized(pixel2.getColor(j-3), (unsigned char)(255), (unsigned char)(0));
            }
        }

        for(int a = 0; a < 3; a++) {
            float num = 1 - (1 - arr[a]) * (1 - arr[a + 3]);
            if(num > 1) {
                num = 1;
            } else if (num < 0) {
                num = 0;
            }
            tmparr[a] = (unsigned char)(num * 255 + 0.5f);
        }

        Pixel newPixel(tmparr[0], tmparr[1], tmparr[2]);
        newImage.addPixel(newPixel);
    }
    return newImage;
}

Image Tasks::overlay(Image &image1, Image &image2) {
    header = image1.getHeader();
    int count = image1.getPixelCount();
    Image newImage(header);
    float arr[6];
    unsigned char tmparr[3];
    for (int i = 0; i < count; i++) {
        Pixel pixel1 = image1.getPixel(i);
        Pixel pixel2 = image2.getPixel(i);
        for (int j = 0; j < 6; j++) {
            if (j < 3) {
                arr[j] = normalized(pixel1.getColor(j), (unsigned char) (255), (unsigned char) (0));
            } else {
                arr[j] = normalized(pixel2.getColor(j - 3), (unsigned char) (255), (unsigned char) (0));
            }
        }
        for (int a = 0; a < 3; a++) {
            if (arr[a + 3] <= 0.5) {
                float num = (2 * arr[a] * arr[a + 3]);
                if (num > 1) {
                    a = 1;
                }
                tmparr[a] = (unsigned char) (num * 255 + 0.5f);
            } else {
                float num = 1 - (2 * (1 - arr[a]) * (1 - arr[a + 3]));
                if (num > 1) {
                    num = 1;
                } else if (num < 0) {
                    num = 0;
                }
                tmparr[a] = (unsigned char) (num * 255 + 0.5f);
            }
        }
        Pixel newPixel(tmparr[0], tmparr[1], tmparr[2]);
        newImage.addPixel(newPixel);
    }
    return newImage;
}

Image Tasks::scale(Image &image, bool value1, float blueScale, bool value2, float greenScale, bool value3,
                      float redScale) {
    header = image.getHeader();
    Image newImage(header);
    unsigned char arr[3];
    unsigned char tmparr[3];
    int count = image.getPixelCount();
    for(int i = 0; i < count; i++) {
        Pixel pixel = image.getPixel(i);
        for(int j = 0; j < 3; j++) {
            arr[j] = pixel.getColor(j);
        }
        if (value1) {
            if (arr[0] * blueScale > (unsigned char)(255)) {
              tmparr[0] = (unsigned char)(255);
            } else {
                tmparr[0] = (unsigned char)(arr[0] * blueScale);
            }
        } else {
            tmparr[0] = arr[0];
        }
        if (value2) {
            if (arr[1] * greenScale > (unsigned char)(255)) {
                tmparr[1] = (unsigned char)(255);
            } else {
                tmparr[1] = (unsigned char)(arr[1] * greenScale);
            }
        } else {
            tmparr[1] = arr[1];
        }
        if (value3) {
            if (arr[2] * redScale > (unsigned char)(255)) {
                tmparr[2] = (unsigned char)(255);
            } else {
                tmparr[2] = (unsigned char)(arr[2] * redScale);
            }
        } else {
            tmparr[2] = arr[2];
        }
    Pixel newPixel(tmparr[0], tmparr[1], tmparr[2]);
    newImage.addPixel(newPixel);

    }

    return newImage;
}

Image Tasks::combine(Image &image1, Image &image2, Image &image3) {
    header = image1.getHeader();
    Image newImage(header);
    int count = image1.getPixelCount();
    unsigned char arr[3];
    for(int i = 0; i < count; i++) {
        arr[0] = image1.getPixel(i).getColor(0);
        arr[1] = image2.getPixel(i).getColor(0);
        arr[2] = image3.getPixel(i).getColor(0);
        Pixel pixel(arr[0], arr[1], arr[2]);
        newImage.addPixel(pixel);
    }

    return newImage;
}

Image Tasks::addColor(Image &image, int _blue, int _green, int _red) {
    header = image.getHeader();
    Image newImage(header);
    int count = image.getPixelCount();
    int arr[3];
    int num;
    int temp;
    unsigned char tmparr[3];
    for (int i = 0; i < count; i++) {
        Pixel pixel = image.getPixel(i);
        for (int j = 0; j < 3; j++) {
            arr[j] = pixel.getColor(j);
            if (j == 0) {
                if (_blue != 0) {
                    if (_blue < 0) {
                        temp = -1 * _blue;
                        num = max(0, arr[j] - temp);
                    } else {
                        temp = _blue;
                        num = min(255, arr[j] + temp);
                    }
                } else {num = arr[j];}
            } else if (j == 1) {
                if (_green != 0) {
                    if (_green < 0) {
                        temp = -1 * _green;
                        num = max(0, arr[j] - temp);
                    } else {
                        temp = _green;
                        num = min(255, arr[j] + temp);
                    }
                } else {num = arr[j];}
            } else if (j == 2) {
                if (_red != 0) {
                    if (_red < 0) {
                        temp = -1 * _red;
                        num = max(0, arr[j] - temp);
                    } else {
                        temp = _red;
                        num = min(255, arr[j] + temp);
                    }
                } else {num = arr[j];}

            }
            tmparr[j] = (unsigned char)num;
        }
        Pixel newPixel(tmparr[0], tmparr[1], tmparr[2]);
        newImage.addPixel(newPixel);
    }
    return newImage;
}

                /*
                arr[j] = normalized(pixel.getColor(j), (unsigned char)(255), (unsigned char)(0));
                float num = arr[0] + normalized(_blue, (unsigned char)(255),(unsigned char)(0));
                if(num > 1) {
                    num = 1;
                }
                tmparr[0] = (unsigned char)(num * 255 + 0.5f);

                num = arr[1] + normalized(_green, (unsigned char)(255),(unsigned char)(0));
                if(num > 1) {
                    num = 1;
                }
                tmparr[1] = (unsigned char)(num * 255 + 0.5f);

                num = arr[2] + normalized(_red, (unsigned char)(255),(unsigned char)(0));
                if(num > 1) {
                    num = 1;
                }
                tmparr[2] = (unsigned char)(num * 255 + 0.5f);
            }*/
