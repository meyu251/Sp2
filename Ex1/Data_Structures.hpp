#pragma once

#include <stdexcept>

namespace graph {
    
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
    template <typename T1, typename T2>
    class Pair{   
    public:
        T1 first;
        T2 second;

        Pair(){};
        Pair(T1 first, T2 second);
    };  // class Pair

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

}  // namespace graph