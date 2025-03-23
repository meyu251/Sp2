#include "Data_Structures.hpp"
#include <stdexcept>  // עבור std::out_of_range

namespace graph {

// מימוש המחלקה DynamicArray

DynamicArray::DynamicArray() {
    size = 0;
    capacity = 1;
    arr = new int[capacity];
}

DynamicArray::DynamicArray(const DynamicArray& other) {
    size = other.size;
    capacity = other.capacity;
    arr = new int[capacity];
    for (int i = 0; i < size; i++) {
        arr[i] = other.arr[i];
    }
}

DynamicArray::~DynamicArray() {
    delete[] arr;
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
    if (this != &other) {
        delete[] arr;
        size = other.size;
        capacity = other.capacity;
        arr = new int[capacity];
        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

void DynamicArray::push_back(int value) {
    if (size == capacity) {
        // הגדלת המערך פי 2 אם הגענו לקיבולת המקסימלית
        capacity *= 2;
        int* newArr = new int[capacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }
    arr[size++] = value;
}

void DynamicArray::pop_back() {
    if (size > 0) {
        size--;
    }
}

int DynamicArray::at(int index) const {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    throw std::out_of_range("Index out of range");
}

int& DynamicArray::at(int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    throw std::out_of_range("Index out of range");
}

int DynamicArray::getSize() const {
    return size;
}

bool DynamicArray::isEmpty() const {
    return size == 0;
}

void DynamicArray::clear() {
    size = 0;
}

bool DynamicArray::contains(int value) const {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

bool DynamicArray::remove(int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            // הזזת כל האיברים שמאלה
            for (int j = i; j < size - 1; j++) {
                arr[j] = arr[j + 1];
            }
            size--;
            return true;
        }
    }
    return false;
}

// מימוש המחלקה Queue

Queue::Queue(int cap) {
    capacity = cap;
    arr = new int[capacity];
    front = 0;
    rear = 0;
    size = 0;
}

Queue::~Queue() {
    delete[] arr;
}

void Queue::enqueue(int value) {
    if (isFull()) {
        throw std::out_of_range("Queue is full");
    }
    
    arr[rear] = value;
    rear = (rear + 1) % capacity;  // מעגלי - חוזר להתחלה אם הגענו לסוף המערך
    size++;
}

int Queue::dequeue() {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    
    int value = arr[front];
    front = (front + 1) % capacity;  // מעגלי
    size--;
    return value;
}

int Queue::peek() const {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    
    return arr[front];
}

bool Queue::isEmpty() const {
    return size == 0;
}

bool Queue::isFull() const {
    return size == capacity;
}

int Queue::getSize() const {
    return size;
}

}  // namespace graph