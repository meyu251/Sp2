/*
author: Meir Yust
mail: meyu251@gmail.com
*/

#include <iostream>
#include "Algorithms.hpp"
 
using namespace std;
using namespace graph;
 
int main(){

    Graph g(5);
    g.addEdge(1, 2, 10);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 2);
    g.addEdge(2, 4, 1);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 2);
    g.addEdge(4, 5, 4);

    cout << "Original Graph:" << endl;
    g.printGraph();
    cout << endl;
         
    Graph bfsResult = bfs(g, 3);
    cout << "BFS Result:" << endl;
    bfsResult.printGraph();
    cout << endl;
    

    Graph dfsResult = dfs(g, 1);
    cout << "DFS Result:" << endl;
    dfsResult.printGraph();
    cout << endl;

    Graph dijkstraResult = dijkstra(g, 1);
    cout << "Dijkstra Result:" << endl;
    dijkstraResult.printGraph();
    cout << endl;

    Graph primResult = prim(g);
    cout << "Prim Result:" << endl;
    primResult.printGraph();
    cout << endl;

    Graph kruskalResult = kruskal(g);
    cout << "Kruskal Result:" << endl;
    kruskalResult.printGraph();
    cout << endl;

    return 0;
}