#pragma once

#include <iostream>
#include "Data_Structures.hpp"

namespace graph {

    class Graph {
    private:
        // becouse the vertex numbered from 1 to n
        // the array at index i represents the adjacency list of vertex (i+1)
        DynamicArray<Pair<int, int>>* adjList;  // first = vertex, second = list of pairs (neighbor, weight)
        int numOfVertices;

    public:
        
        Graph(int n);
        ~Graph();

        void addEdge(int src, int dest, int weight);
        void addEdge(int src, int dest);
        bool hasEdge(int src, int dest);
        void removeEdge(int src, int dest);
        void printGraph();
        

    };

}  // namespace graph