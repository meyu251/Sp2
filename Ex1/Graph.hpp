#pragma once

#include <iostream>
#include "Data_Structures.hpp"

namespace graph {

    class Graph {
    private:
        int numOfVertices;
        Pair<int, DynamicArray<Pair<int, int>>>* adjList;  // first = vertex, second = list of pairs (neighbor, weight)

    public:
        
        Graph(int n);
        ~Graph();

    };

}  // namespace graph