//orbibiariel@gmail.com
#include "Queue.h"
#include <stdexcept>

// Constructor to initialize the queue with a given size
Queue::Queue(int size) {
    this->size = size;
    arr = new int[size];
    first = -1;
    last = -1;
}

// Destructor to clean up the allocated memory
Queue::~Queue() {
    delete[] arr;
}

// Check if the queue is empty
bool Queue::isEmpty() {
    return first == -1;
}

// Check if the queue is full
bool Queue::isFull() {
    return (last + 1) % size == first;
}

// Add an element to the queue
void Queue::enqueue(int value) {
    if (isFull()) {
        throw std::overflow_error("Queue is full");
    }
    if (first == -1) first = 0;
    last = (last + 1) % size;
    arr[last] = value;
}

// Remove an element from the queue
int Queue::dequeue() {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    }
    int value = arr[first];
    if (first == last) {
        first = last = -1;
    } else {
        first = (first + 1) % size;
    }
    return value;
}
