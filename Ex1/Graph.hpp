/*
author: Meir Yust
mail: meyu251@gmail.com
*/

#pragma once

#include <iostream>
#include "Data_Structures.hpp"

namespace graph {

    class Graph{
    private:
        // becouse the vertex numbered from 1 to n
        // the list at index i represents the adjacency list of vertex (i+1)
        DynamicArray<Pair<int, int>>* adjList;  // list of pairs (neighbor, weight)
        int numOfVertices;

    public:
        
        Graph(int n);
        Graph(const Graph& g);    // copy constructor
        ~Graph();
        Graph& operator=(const Graph& other);

        int getNumOfVertices();
        void addEdge(int src, int dest, int weight);
        void addEdge(int src, int dest);
        void addDirectedEdge(int src, int dest, int weight);
        void addDirectedEdge(int src, int dest);
        bool hasEdge(int src, int dest);
        void removeEdge(int src, int dest);
        void printGraph();
        DynamicArray<Pair<int, int>> getNeighbors(int vertex);
        bool hasNegativeEdge();
    
    };  // class Graph

}  // namespace graph