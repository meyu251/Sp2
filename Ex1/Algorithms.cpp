#include <iostream>
#include "Data_Structures.hpp"
#include "Graph.hpp"
#include "Algorithms.hpp"

using namespace graph;

Graph bfs(Graph& g, int root){
    Graph ans(g.getNumOfVertices());
    DynamicArray<bool> visited(g.getNumOfVertices());
    for(int i = 0; i < visited.getSize(); i++){
        visited[i] = false;
    }
    Queue<int> q;

    q.enqueue(root);
    visited[root - 1] = true;   // the -1 is becouse the vertex numbered from 1 to n and the array from 0 to n-1

    while(!q.isEmpty()){
        int current = q.dequeue();
        DynamicArray<Pair<int, int>> neighbors = g.getNeighbors(current);
        for(int i = 0; i < neighbors.getSize(); i++){
            int neighbor = neighbors[i].first;
            if(!visited[neighbor - 1]){
                q.enqueue(neighbor);
                visited[neighbor - 1] = true;
                ans.addEdge(current, neighbor, neighbors[i].second);    // add also the original weight of this edge
            }
        }
    }

    return ans;
}

Graph dfs(Graph& g, int root){
    Graph ans(g.getNumOfVertices());
    DynamicArray<int> visited(g.getNumOfVertices()); // consider 0 as not visited, 1 as visited but not finished, 2 as visited and finished
    for(int i = 0; i < visited.getSize(); i++){
        visited[i] = 0;
    }
    Stack<int> s;
    s.push(root);
    visited[root - 1] = 1;   // the -1 is becouse the vertex numbered from 1 to n and the array from 0 to n-1

    while(!s.isEmpty()){
        int current = s.peek(); // doesn't remove it from the stack yet
        DynamicArray<Pair<int, int>> neighbors = g.getNeighbors(current);
        bool allVisited = true;
        for(int i = 0; i < neighbors.getSize(); i++){
            int neighbor = neighbors[i].first;
            if(visited[neighbor - 1] == 0){ // only if not visited at all
                s.push(neighbor);
                visited[neighbor - 1] = 1;
                ans.addEdge(current, neighbor, neighbors[i].second);    // add also the original weight of this edge
                allVisited = false;
                break;
            }
        }
        if(allVisited){ // all neighbors are visited so we can finish this vertex
            visited[current - 1] = 2;
            s.pop();
        }
    }

    return ans;
}