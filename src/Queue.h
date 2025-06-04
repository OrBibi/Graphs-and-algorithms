//orbibiariel@gmail.com
#ifndef QUEUE_H
#define QUEUE_H

class Queue {
public:
    // Constructor
    Queue(int size);

    // Destructor
    ~Queue();

    // Function to check if the queue is empty
    bool isEmpty();

    // Function to check if the queue is full
    bool isFull();

    // Function to add an element to the queue
    void enqueue(int value);

    // Function to remove an element from the queue
    int dequeue();

private:
    int* arr;  // Pointer to the dynamic array that holds the queue's elements
    int size;  // Size of the queue
    int first, last;  // Indices for the front and rear of the queue
};

#endif
