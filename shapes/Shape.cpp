#include <iostream>
//#include <math.h>
using namespace std;

#include "Shape.h"

Shape::Shape() {
    length = 0;
    width = 0;
}

Shape::~Shape() {
    length = 0;
    width = 0;
}


Shape2D::Shape2D() {
    length = 0;
    width = 0;
}

Shape2D::~Shape2D() {
    length = 0;
    width = 0;
}

void Shape2D::ShowArea() const {
    cout << GetName2D() << endl;
    cout << Area() << endl;
}

bool Shape2D::operator<(const Shape2D &rhs) const {
    if (Area() < rhs.Area()) {
        return true;
    } else {
        return false;
    }
}

bool Shape2D::operator==(const Shape2D &rhs) const {
    if (Area() == rhs.Area()) {
        return true;
    } else {
        return false;
    }
}

bool Shape2D::operator>(const Shape2D &rhs) const {
    if (Area() > rhs.Area()) {
        return true;
    } else {
        return false;
    }
}

Shape3D::Shape3D() {
    length = 0;
    width = 0;
    height = 0;
}

Shape3D::~Shape3D() {
    length = 0;
    width = 0;
    height = 0;
}

void Shape3D::ShowVolume() const {
    cout << GetName3D() << endl;
    cout << Volume() << endl;
}

bool Shape3D::operator>(const Shape3D &rhs) const {
    if (Volume() > rhs.Volume()) {
        return true;
    } else {
        return false;
    }
}

bool Shape3D::operator==(const Shape3D &rhs) const {
    if (Volume() == rhs.Volume()) {
        return true;
    } else {
        return false;
    }
}

bool Shape3D::operator<(const Shape3D &rhs) const {
    if (Volume() < rhs.Volume()) {
        return true;
    } else {
        return false;
    }
}


Square::Square() {
    length = 0;
}

Square::Square(float userLength) {
    length = userLength;
}

void Square::Scale(float scaleFactor) {
    length *= scaleFactor;
    cout << "The new scaled length is " << length << endl;
}

float Square::Area() const  {
    return length * length;
}

string Square::GetName2D() const {
    return "square";
}

void Square::Display() const {
    cout << "The area of the Square is: " << Area() << endl << "Length of a side is: " << length << endl;
}

Square::~Square() {
    length = 0;
}

Triangle::Triangle() {
    base = 0;
    height = 0;
}

Triangle::Triangle(float userBase, float userHeight) {
    base = userBase;
    height = userHeight;
}

Triangle::~Triangle() {
    base = 0;
    height = 0;
}

string Triangle::GetName2D() const {
    return "triangle";
}

float Triangle::Area() const {
    return (base * height) / 2;
}

void Triangle::Display() const {
    cout << "The area of the Triangle is " << Area() << endl << "Base: " << base << endl << "Height: " << height << endl;
}

void Triangle::Scale(float scaleFactor) {
    base *= scaleFactor;
    height *= scaleFactor;
}

Circle::Circle() {
    radius = 0;
}

Circle::Circle(float userRadius) {
    radius = userRadius;
}

Circle::~Circle() {
    radius = 0;
}

void Circle::Scale(float scaleFactor) {
    radius *= scaleFactor;
}

float Circle::Area() const {
    return pi * (radius * radius);
}

string Circle::GetName2D() const {
    return "circle";
}

void Circle::Display() const {
    cout << "The area of the Circle is: " << Area() << endl << "Radius: " << radius << endl;
}

float Circle::GetRadius() const {
    return radius;
}

TriangularPyramid::TriangularPyramid() {
    pyramidHeight = 0;
    length = 0;
    baseHeight = 0;
}

TriangularPyramid::~TriangularPyramid() {
    pyramidHeight = 0;
    length = 0;
    baseHeight = 0;
}

TriangularPyramid::TriangularPyramid(float pHeight, float length1, float bHeight) : Triangle(length1, bHeight){
    pyramidHeight = pHeight;
    length = length1;
    baseHeight = bHeight;
}

float TriangularPyramid::Volume() const {
    return ((Triangle::Area() * pyramidHeight) * (1.0/3.0));
}

string TriangularPyramid::GetName3D() const {
    return "TriangularPyramid";
}

void TriangularPyramid::Display() const {
    cout << "The volume of the TriangularPyramid is: " << Volume() << endl << "The height is: " << pyramidHeight << endl << "The area of the Triangle is: " << Triangle::Area() << endl << "Base: " << length << endl << "Height: " << baseHeight << endl;
}

void TriangularPyramid::Scale(float scaleFactor) {
    length *= scaleFactor;
    pyramidHeight *= scaleFactor;
    baseHeight *= scaleFactor;
}

Cylinder::Cylinder() {
    height = 0;
    radius = 0;
}

Cylinder::Cylinder(float userHeight, float userRadius) : Circle(userRadius) {
    height = userHeight;
    radius = userRadius;
}

Cylinder::~Cylinder() {
    height = 0;
    radius = 0;
}

float Cylinder::Volume() const {
    return Circle::Area() * height;
}

void Cylinder::Scale(float scaleFactor) {
    height *= scaleFactor;
    radius *= scaleFactor;
}

void Cylinder::Display() const {
    cout << "The volume of the Cylinder is: " << Volume() << endl << "The height is: " << height << endl << "The area of the Circle is: " << Circle::Area() << endl << "Radius: " << radius << endl;
}

string Cylinder::GetName3D() const {
    return "Cylinder";
}

Sphere::Sphere() {
    radius = 0;
}

Sphere::Sphere(float userRadius) : Circle(userRadius){
    radius = userRadius;
}

Sphere::~Sphere() {
    radius = 0;
}

float Sphere::Volume() const {
    return (4/3) * pi * pow((Circle::GetRadius()), 3);
}

void Sphere::Scale(float scaleFactor) {
    radius *= scaleFactor;
}

string Sphere::GetName3D() const {
    return "Sphere";
}

void Sphere::Display() const {
    cout << "The volume of the Sphere is: " << Volume() << endl << "The area of the Circle is: " << Circle::Area() << endl << "Radius: " << radius << endl;
}