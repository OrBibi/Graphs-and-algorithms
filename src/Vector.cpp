//orbibiariel@gmail.com
#include "Vector.h"
#include <iostream>
#include <stdexcept> 

// Constructor with initial size (default 10)
Vector::Vector(int initialSize) {
    size = 0;
    capacity = initialSize;
    arr = new int[capacity];
}

// Destructor
Vector::~Vector() {
    delete[] arr;
}

// Adds a value to the vector
void Vector::push_back(int value) {
    if (size == capacity) {
        resize(capacity * 2);  // Double the capacity when full
    }
    arr[size++] = value;
}

// Access element by index (getter)
int Vector::get(int index) const {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    throw std::out_of_range("Index is out of range");
}

// Set element by index (setter)
void Vector::set(int index, int value) {
    if (index >= 0 && index < size) {
        arr[index] = value;
    }
}

// Returns the current size of the vector
int Vector::getSize() {
    return size;
}

// Returns the capacity of the vector
int Vector::getCapacity() const {
    return capacity;
}

// Resize function for increasing vector size
void Vector::resize(int newCapacity) {
    capacity = newCapacity;
    int* newArr = new int[capacity];
    for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
}
