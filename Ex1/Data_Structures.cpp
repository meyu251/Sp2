#include "Data_Structures.hpp"
#include <stdexcept>
#include <algorithm>

namespace graph {

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
DynamicArray<T>::~DynamicArray(){
    delete[] data;
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


//////////////////////////////////////////
// Pair
//////////////////////////////////////////
template <typename T1, typename T2>
Pair<T1, T2>::Pair(T1 first, T2 second){
    this->first = first;
    this->second = second;
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
        data.push_back(value);
    }
    else{
        data[tail] = value;
    }
    tail = (tail + 1) % data.getSize();
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

}  // namespace graph

template class graph::Pair<int, int>;
template class graph::DynamicArray<int>;
template class graph::DynamicArray<bool>;
template class graph::DynamicArray<graph::Pair<int, int>>;
template class graph::Queue<int>;