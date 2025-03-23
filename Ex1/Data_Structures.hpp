#pragma once

#include <stdexcept>

namespace graph {

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
    };

    template <typename T1, typename T2>
    class Pair{
        public:
        T1 first;
        T2 second;

        Pair(){};
        Pair(T1 first, T2 second){
            this->first = first;
            this->second = second;
        }
    };

}  // namespace graph