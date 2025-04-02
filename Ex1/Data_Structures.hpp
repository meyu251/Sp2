/*
author: Meir Yust
mail: meyu251@gmail.com
*/

#pragma once

#include <stdexcept>

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
        ~DynamicArray();

        void push_back(const T& value); // add an element to the end of the array
        void removeAt(int index);
        T& get(int index);
        int getSize() const;
        bool isEmpty() const;
        T& operator[](int index);
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

    ////////////////////////////////////////////
    // PriorityQueue
    ////////////////////////////////////////////
    template <typename T>
    class PriorityQueue {
    private:
        DynamicArray<T> data;
        int size;

        void heapifyUp(int index);
        void heapifyDown(int index);

    public:
        PriorityQueue();
        ~PriorityQueue();

        void enqueue(const T& value);
        T dequeue();
        T peek();
        int getSize() const;
        bool isEmpty() const;
    };  // class PriorityQueue

}  // namespace graph

template class graph::Pair<int, int>;
template class graph::DynamicArray<int>;
template class graph::DynamicArray<bool>;
template class graph::DynamicArray<graph::Pair<int, int>>;
template class graph::Queue<int>;
template class graph::Stack<int>;
template class graph::PriorityQueue<graph::Pair<int, int>>;