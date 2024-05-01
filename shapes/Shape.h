#include <iostream>
#include <math.h>
using namespace std;

class Shape {
public:
    float length;
    float width;
    Shape();
    ~Shape();
    virtual void Scale(float scaleFactor) = 0;
    virtual void Display() const = 0;
};

class Shape2D : virtual public Shape {
public:
    float length;
    float width;
    Shape2D();
    ~Shape2D();
    virtual float Area() const = 0;
    void ShowArea() const;
    virtual string GetName2D() const = 0;
    bool operator> (const Shape2D &rhs) const;
    bool operator< (const Shape2D &rhs) const;
    bool operator== (const Shape2D &rhs) const;
};

class Shape3D : virtual public Shape {
public:
    float length;
    float width;
    float height;
    Shape3D();
    ~Shape3D();
    virtual float Volume() const = 0;
    void ShowVolume() const;
    virtual string GetName3D() const = 0;
    bool operator> (const Shape3D &rhs) const;
    bool operator< (const Shape3D &rhs) const;
    bool operator== (const Shape3D &rhs) const;
};


class Square : public Shape2D  {
public:
    float length;
    Square();
    ~Square();
    Square(float userLength);
    void Scale(float scaleFactor);
    void Display() const;
    float Area() const;
    string GetName2D() const;
};

class Triangle : public Shape2D {
public:
    float base;
    float height;
    Triangle();
    Triangle(float userBase, float userHeight);
    ~Triangle();
    void Scale(float scaleFactor);
    void Display() const;
    float Area() const;
    string GetName2D() const;
};

class Circle : public Shape2D {
public:
    float radius;
    float pi = 3.14159f;
    Circle();
    Circle(float userRadius);
    ~Circle();
    void Scale(float scaleFactor);
    void Display() const;
    float Area() const;
    string GetName2D() const;
    float GetRadius() const;
};

class TriangularPyramid : public Shape3D, private Triangle {
public:
    float pyramidHeight;
    float length;
    float baseHeight;
    TriangularPyramid();
    ~TriangularPyramid();
    TriangularPyramid(float pHeight, float length1, float bHeight);
    float Volume() const;
    string GetName3D() const;
    void Scale(float scaleFactor);
    void Display() const;
};


class Cylinder : public Shape3D, private Circle {
public:
    float radius;
    float height;
    Cylinder();
    ~Cylinder();
    Cylinder(float userHeight, float userRadius);
    float Volume() const;
    string GetName3D() const;
    void Scale(float scaleFactor);
    void Display() const;
};


class Sphere : public Shape3D, private Circle {
public:
    float radius;
    float pi = 3.14159f;
    Sphere();
    Sphere(float userRadius);
    ~Sphere();
    float Volume() const;
    string GetName3D() const;
    void Scale(float scaleFactor);
    void Display() const;
};



















