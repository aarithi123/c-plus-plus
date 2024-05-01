//
// Created by aarit on 12/26/2023.
//

#pragma once
#include <iostream>
using namespace std;

template <typename T>
class ABQ {
public:
    int holding;
    int currSize;
    T* tower;
    T* newTower;
    T element;
    int newHolding = 0;
    float scaleFactor = 2.0f;

    ABQ();

    ABQ(int capacity);

    ABQ(const ABQ &d);

    ABQ &operator= (const ABQ &d);

    ~ABQ();

    void enqueue(T data);

    T dequeue();

    T peek();

    unsigned int getSize();

    unsigned int getMaxCapacity();

    T* getData();

};

template <typename T>
ABQ<T>::ABQ() {
    holding = 1;
    currSize = 0;
    tower = new T[holding];
}
template <typename T>
ABQ<T>::ABQ(int capacity) {
    holding = capacity;
    currSize = 0;
    tower = new T[capacity];
}
template <typename T>
ABQ<T>::ABQ(const ABQ<T> &d) {
    currSize = d.currSize;
    holding = d.holding;
    tower = new T[d.holding];
    for (int i = 0; i < d.holding; i++) {
        tower[i] = d.tower[i];
    }
}
template <typename T>
ABQ<T> &ABQ<T>::operator=(const ABQ<T> &d) {
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
ABQ<T>::~ABQ() {
    delete[] tower;
}

template <typename T>
void ABQ<T>::enqueue(T data) {
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
    currSize++;
}

template <typename T>
T ABQ<T>::dequeue() {
    if (currSize == 0) {
        throw runtime_error ("An error has occurred.");
    }
    else if (((float)(currSize - 1)/holding) < (1/scaleFactor)){
        element = tower[0];
        newHolding = holding / 2;
        newTower = new T[newHolding];
        for (int x = 1; x < (currSize); x++) {
            newTower[x - 1] = tower[x];
        }
        delete[] tower;
        tower = newTower;
        holding = newHolding;

    } else {
        element = tower[0];
        newTower = new T[holding];
        for (int r = 1; r < (currSize); r++) {
            newTower[r - 1] = tower[r];
        }
        delete[] tower;
        tower = newTower;
    }
    currSize--;
    return element;
}

template <typename T>
T ABQ<T>::peek() {
    if (currSize == 0) {
        throw runtime_error("An error has occurred.");
    }
    else {//return value at the front of the queue
        return tower[0];
    }
}
template <typename T>
unsigned int ABQ<T>::getSize() {
    return currSize;
}
template <typename T>
unsigned int ABQ<T>::getMaxCapacity() {
    return holding;
}
template <typename T>
T *ABQ<T>::getData() {
    return tower;
}



