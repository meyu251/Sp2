#include "Graph.hpp"
#include <iostream>

namespace graph {

Graph::Graph(int n){
    adjList = new DynamicArray<Pair<int, int>>[n];  // first = neighbore, second = weight
    int numOfVertices = n;
}

Graph::~Graph(){
    delete[] adjList;
}

void Graph::addEdge(int src, int dest, int weight){
    adjList[src - 1].push_back({dest, weight});
    adjList[dest - 1].push_back({src, weight});
}

/*
Add an undirected edge between src and dest
*/
void Graph::addEdge(int src, int dest){
    adjList[src - 1].push_back({dest, 1});
    adjList[dest - 1].push_back({src, 1});
}

bool Graph::hasEdge(int src, int dest){
    for(int i = 0; i < adjList[src - 1].getSize(); i++){
        if(adjList[src - 1].get(i).first == dest){
            return true;
        }
    }
    return false;
}

/*
Remove an undirected edge between src and dest
*/
void Graph::removeEdge(int src, int dest){
    if(!hasEdge(src, dest)){
        throw std::invalid_argument("Edge does not exist.");
        return;
    }

    for(int i = 0; i < adjList[src - 1].getSize(); i++){
        if(adjList[src - 1].get(i).first == dest){
            adjList[src - 1].removeAt(i);
            break;
        }
    }
    for(int i = 0; i < adjList[dest - 1].getSize(); i++){
        if(adjList[dest - 1].get(i).first == src){
            adjList[dest - 1].removeAt(i);
            break;
        }
    }
}

/*
Print the graph in the following format:
{vertex1, neighbor (weight)}, {vertex1, neighbor (weight)}, ...
{vertex2, neighbor (weight)}, {vertex2, neighbor (weight)}, ...
.
.
.
{vertexN, neighbor (weight)}, {vertexN, neighbor (weight)}, ..
*/
void Graph::printGraph(){
    for(int i = 0; i < numOfVertices; i++){
        for(int j = 0; j < adjList[i].getSize(); j++){
            std::cout << "{" << i+1 << "," << adjList[i].get(j).first << " (" << adjList[i].get(j).second << ")}";
            if(j != adjList[i].getSize() - 1){
                std::cout << ", ";
            }
            else{
                std::cout << std::endl;
            }
        }
    }
}

}  // namespace graph