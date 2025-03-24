#include <iostream>
#include "Graph.hpp"

using namespace graph;

int main() {
    
    Graph g(5);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);

    g.printGraph();
    
    return 0;
}
