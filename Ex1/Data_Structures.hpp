/*
author: Meir Yust
mail: meyu251@gmail.com
*/

#pragma once

#include <stdexcept>
#include <algorithm>

namespace graph {
    
    //////////////////////////////////////////
    // DynamicArray
    //////////////////////////////////////////
    template <typename T>
    class DynamicArray {
    private:
        T* data;
        int capacity;
        int size;   // current size of the array

        void resize(int newCapacity);

    public:

        DynamicArray();
        DynamicArray(int capacity);
        DynamicArray(const DynamicArray& other);
        ~DynamicArray();
        DynamicArray& operator=(const DynamicArray& other);

        void push_back(const T& value); // add an element to the end of the array
        void removeAt(int index);
        T& get(int index);
        int getSize() const;
        bool isEmpty() const;
        T& operator[](int index);
        const T& operator[](int index) const;
    };  // class DynamicArray


    //////////////////////////////////////////
    // Pair
    //////////////////////////////////////////
    template <typename T1, typename T2>
    class Pair{   
    public:
        T1 first;
        T2 second;

        Pair(){};
        Pair(T1 first, T2 second);
        bool operator<(const Pair<T1, T2>& other) const;
    };  // class Pair

    //////////////////////////////////////////
    // Queue
    //////////////////////////////////////////
    template <typename T>
    class Queue {
    private:
        DynamicArray<T> data;
        int head;
        int tail;
        int size;
        
    public:
        Queue();
        ~Queue();

        void enqueue(const T& value);
        T dequeue();
        T peek();
        int getSize() const;
        bool isEmpty() const;
        
    };  // class Queue

    //////////////////////////////////////////
    // Stack
    //////////////////////////////////////////
    template <typename T>
    class Stack {
    private:
        DynamicArray<T> data;
        int top;
        int size;

    public:
        Stack();
        ~Stack();

        void push(const T& value);
        T pop();
        T peek();
        int getSize() const;
        bool isEmpty() const;
    };  // class Stack

    //////////////////////////////////////////
    // PriorityQueue
    //////////////////////////////////////////
    template <typename T>
    class PriorityQueue {
    private:
        DynamicArray<T> heap;
        int size;

        void heapifyUp(int index);
        void heapifyDown(int index);

    public:
        PriorityQueue();
        ~PriorityQueue();

        void enqueue(const T& value);
        T dequeue();
        const T& peek() const;
        int getSize() const;
        bool isEmpty() const;
        void printHeap() const;
    };


//////////////////////////////////////////
// DynamicArray
//////////////////////////////////////////    
template <typename T>
DynamicArray<T>::DynamicArray(){
    capacity = 2;
    size = 0;
    data = new T[capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(int capacity){
    if(capacity <= 0){
        throw std::invalid_argument("Capacity must be greater than 0");
    }
    this->capacity = capacity;
    size = 0;
    data = new T[capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other){
    capacity = other.capacity;
    size = other.size;
    data = new T[capacity];
    std::copy(other.data, other.data + size, data);
}

template <typename T>
DynamicArray<T>::~DynamicArray(){
    delete[] data;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other){
    if(this != &other){
        delete[] data;
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        std::copy(other.data, other.data + size, data);
    }
    return *this;
}

template <typename T>
void DynamicArray<T>::resize(int newCapacity){
    if(newCapacity <= 0){
        throw std::invalid_argument("New capacity must be greater than 0");
    }
    T* newData = new T[newCapacity];
    std::copy(data, data + size, newData);
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template <typename T>
void DynamicArray<T>::push_back(const T& value){
    if(size == capacity){
        resize(capacity * 2);
    }
    data[size++] = value;
}

template <typename T>
void DynamicArray<T>::removeAt(int index){
    if(index < 0 || index >= size){
        throw std::out_of_range("Index out of range");
    }
    for(int i = index; i < size - 1; i++){
        data[i] = data[i + 1];
    }
    size--;
}

template <typename T>
T& DynamicArray<T>::get(int index){
    if(index < 0 || index >= size){
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
int DynamicArray<T>::getSize() const{
    return size;
}

template <typename T>
bool DynamicArray<T>::isEmpty() const{
    return size == 0;
}

template <typename T>
T& DynamicArray<T>::operator[](int index){
    if(index < 0 || index >= size){
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
const T& DynamicArray<T>::operator[](int index) const{
    if(index < 0 || index >= size){
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}


//////////////////////////////////////////
// Pair
//////////////////////////////////////////
template <typename T1, typename T2>
Pair<T1, T2>::Pair(T1 first, T2 second){
    this->first = first;
    this->second = second;
}

template <typename T1, typename T2>
bool Pair<T1, T2>::operator<(const Pair<T1, T2>& other) const{
    return this->second < other.second;
}


//////////////////////////////////////////
// Queue
//////////////////////////////////////////
template <typename T>
Queue<T>::Queue(){
    head = 0;
    tail = 0;
    size = 0;
}

template <typename T>
Queue<T>::~Queue(){}

template <typename T>
void Queue<T>::enqueue(const T& value){
    if(size == data.getSize()){
        int oldSize = data.getSize();
        data.push_back(value);
        tail = (tail + 1) % (oldSize == 0 ? 1 : oldSize);
    }
    else{
        data[tail] = value;
        tail = (tail + 1) % data.getSize();
    }
    size++;
}

template <typename T>
T Queue<T>::dequeue(){
    if(size == 0){
        throw std::out_of_range("Queue is empty");
    }
    T value = data[head];
    head = (head + 1) % data.getSize();
    size--;
    return value;
}

template <typename T>
T Queue<T>::peek(){
    if(size == 0){
        throw std::out_of_range("Queue is empty");
    }
    return data[head];
}

template <typename T>
int Queue<T>::getSize() const{
    return size;
}

template <typename T>
bool Queue<T>::isEmpty() const{
    return size == 0;
}

//////////////////////////////////////////
// Stack
//////////////////////////////////////////
template <typename T>
Stack<T>::Stack(){
    top = -1;
    size = 0;
}

template <typename T>
Stack<T>::~Stack(){}

template <typename T>
void Stack<T>::push(const T& value){
    if(size == data.getSize()){
        data.push_back(value);
    }
    else{
        data[size] = value;
    }
    top++;
    size++;
}

template <typename T>
T Stack<T>::pop(){
    if(size == 0){
        throw std::out_of_range("Stack is empty");
    }
    size--;
    return data[top--];
}

template <typename T>
T Stack<T>::peek(){
    if(size == 0){
        throw std::out_of_range("Stack is empty");
    }
    return data[top];
}

template <typename T>
int Stack<T>::getSize() const{
    return size;
}

template <typename T>
bool Stack<T>::isEmpty() const{
    return size == 0;
}

//////////////////////////////////////////
// PriorityQueue
//////////////////////////////////////////
template <typename T>
void PriorityQueue<T>::heapifyUp(int index){
    while(index > 0){
        int parent = (index - 1) / 2;
        if(heap[index] < heap[parent]){
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
        else{
            break;
        }
    }
}

template <typename T>
void PriorityQueue<T>::heapifyDown(int index){
    while(true){
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if(left < size && heap[left] < heap[smallest]){
            smallest = left;
        }
        if(right < size && heap[right] < heap[smallest]){
            smallest = right;
        }
        if(smallest != index){
            std::swap(heap[index], heap[smallest]);
            index = smallest;
        }
        else{
            break;
        }
    }
}

template <typename T>
PriorityQueue<T>::PriorityQueue(){
    size = 0;
}

template <typename T>
PriorityQueue<T>::~PriorityQueue(){}

template <typename T>
void PriorityQueue<T>::enqueue(const T& value){
    heap.push_back(value);
    size++;
    heapifyUp(size - 1);
}

template <typename T>
T PriorityQueue<T>::dequeue(){
    if(size == 0){
        throw std::out_of_range("PriorityQueue is empty");
    }
    T top = heap[0];
    heap[0] = heap[size - 1];
    heap.removeAt(size - 1);
    size--;
    if(size > 0){
        heapifyDown(0);
    }
    return top;
}

template <typename T>
const T& PriorityQueue<T>::peek() const{
    if(size == 0){
        throw std::out_of_range("PriorityQueue is empty");
    }
    return heap[0];
}

template <typename T>
int PriorityQueue<T>::getSize() const {return size;}
template <typename T>
bool PriorityQueue<T>::isEmpty() const{return size == 0;}

template <typename T>
void PriorityQueue<T>::printHeap() const{
    if(size == 0){
        std::cout << "Heap is empty" << std::endl;
        return;
    }
    for(int i = 0; i < size; i++){
        std::cout << "at index " << i << ": " << heap[i].first << ", " << heap[i].second << std::endl;
    }
}

}  // namespace graph

template class graph::Pair<int, int>;
template class graph::DynamicArray<int>;
template class graph::DynamicArray<bool>;
template class graph::DynamicArray<graph::Pair<int, int>>;
template class graph::Queue<int>;
template class graph::Stack<int>;
template class graph::PriorityQueue<graph::Pair<int, int>>;