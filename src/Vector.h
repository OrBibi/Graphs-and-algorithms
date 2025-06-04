//orbibiariel@gmail.com
#ifndef VECTOR_H  
#define VECTOR_H

class Vector {
public:
    // Constructor with initial size (default 10)
    Vector(int initialSize = 10);

    // Destructor
    ~Vector();

    // Adds a value to the vector
    void push_back(int value);

    // Access element by index (getter)
    int get(int index) const;

    // Set element by index (setter)
    void set(int index, int value);

    // Returns the current size of the vector
    int getSize();

    // Returns the capacity of the vector
    int getCapacity() const;

private:
    int* arr;
    int size;
    int capacity;

    // Resize function for increasing vector size
    void resize(int newCapacity);
};

#endif 
