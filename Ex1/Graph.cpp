#include "Graph.hpp"
#include <iostream>

namespace graph {

Graph::Graph(int n){
    numOfVertices = n;
    adjList = new Pair<int, DynamicArray<Pair<int, int>>>[n];  // first = vertex, second = list of pairs (neighbor, weight)
}

Graph::~Graph() {
    delete[] adjList;
}

}  // namespace graph