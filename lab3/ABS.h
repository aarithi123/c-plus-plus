//
// Created by aarit on 12/25/2023.
//
#pragma once
#include <iostream>
using namespace std;

template <typename T>
class ABS {
public:
    int holding;
    int currSize;
    T* tower;
    T* newTower;
    T element;
    int newHolding = 0;
    float scaleFactor = 2.0f;

    ABS();

    ABS(int capacity);

    ABS(const ABS &d);

    ABS &operator= (const ABS &d);

    ~ABS();

    void push(T data);

    T pop();

    T peek();

    unsigned int getSize();

    unsigned int getMaxCapacity();

    T* getData();


};

template <typename T>
ABS<T>::ABS() {
    holding = 1;
    currSize = 0;
    tower = new T[holding];
}
template <typename T>
ABS<T>::ABS(int capacity) {
    holding = capacity;
    currSize = 0;
    tower = new T[capacity];
}
template <typename T>
ABS<T>::ABS(const ABS<T> &d) {
    currSize = d.currSize;
    holding = d.holding;
    tower = new T[d.holding];
    for (int i = 0; i < d.holding; i++) {
        tower[i] = d.tower[i];
    }
}
template <typename T>
ABS<T> &ABS<T>::operator=(const ABS<T> &d) {
    if (this != d) {
        currSize = d.currSize;
        holding = d.holding;
        tower = new T[d.holding];
        for (int i = 0; i < d.holding; i++) {
            tower[i] = d.tower[i];
        }
    }
    return *this;
}
template <typename T>
ABS<T>::~ABS() {
    delete[] tower;
}
template <typename T>
void ABS<T>::push(T data) {
    if (currSize == holding) {
        holding = holding * scaleFactor;
        newTower = new T[holding];
        for (int p = 0; p < currSize; p++) {
            newTower[p] = tower[p];
        }
        delete[] tower;
        tower = newTower;
        tower[currSize] = data;

    } else {
        tower[currSize] = data;
    }
    this->currSize++;
}
template <typename T>
T ABS<T>::pop() {
    if (currSize == 0) {
        throw runtime_error ("An error has occurred.");
    }
    else if (((float)(currSize - 1)/holding) < (1/scaleFactor)){
        element = tower[currSize - 1];
        newHolding = holding / 2;
        newTower = new T[newHolding];
        for (int x = 0; x < (currSize - 1); x++) {
            newTower[x] = tower[x];
        }
        delete[] tower;
        tower = newTower;
        holding = newHolding;

    } else {
        element = tower[currSize - 1];
        newTower = new T[holding];
        for (int r = 0; r < (currSize - 1); r++) {
            newTower[r] = tower[r];
        }
        delete[] tower;
        tower = newTower;
    }
    this->currSize--;
    return element;
}
template <typename T>
T ABS<T>::peek() {
    if (currSize == 0) {
        throw runtime_error("An error has occurred.");
    }
    else {
        //return item top of the stack
        return tower[this->currSize - 1];
    }
}
template <typename T>
unsigned int ABS<T>::getSize() {
    return this->currSize;
}
template <typename T>
unsigned int ABS<T>::getMaxCapacity() {
    return holding;
}
template <typename T>
T *ABS<T>::getData() {
    return tower;
}





ABS();// constructor
template <typename T>
ABS<T>::ABS() {
    holding = 1;
    currSize = 0;
    tower = new T[holding];
ABS(int capacity);// parametized constructor
template <typename T>
ABS<T>::ABS(int capacity) {
    holding = capacity;
    currSize = 0;
    tower = new T[capacity];
}
ABS(const ABS &d);// copy constructor
template <typename T>
ABS<T>::ABS(const ABS<T> &d) {
    currSize = d.currSize;
    holding = d.holding;
    tower = new T[d.holding];
    for (int i = 0; i < d.holding; i++) {
        tower[i] = d.tower[i];
    }
}
ABS &operator= (const ABS &d);// assignment operator
template <typename T>
ABS<T> &ABS<T>::operator=(const ABS<T> &d) {
    if (this != d) {
        currSize = d.currSize;
        holding = d.holding;
        tower = new T[d.holding];
        for (int i = 0; i < d.holding; i++) {
            tower[i] = d.tower[i];
        }
    }
    return *this;
}
~ABS();// destructor
template <typename T>
ABS<T>::~ABS() {
    delete[] tower;
}