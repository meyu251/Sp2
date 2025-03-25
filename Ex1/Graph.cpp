#include "Graph.hpp"
#include <iostream>

namespace graph {

Graph::Graph(int n){
    adjList = new DynamicArray<Pair<int, int>>[n];  // first = neighbore, second = weight
    this->numOfVertices = n;
}

Graph::Graph(Graph& g){
    this->numOfVertices = g.numOfVertices;
    adjList = new DynamicArray<Pair<int, int>>[numOfVertices];
    for(int i = 0; i < numOfVertices; i++){
        for(int j = 0; j < g.adjList[i].getSize(); j++){
            adjList[i].push_back(g.adjList[i].get(j));
        }
    }
}

Graph::~Graph(){
    delete[] adjList;
}

int Graph::getNumOfVertices(){
    return numOfVertices;
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

if there are no edeges for a vertex, print "Vertex i has no neighbors."
*/
void Graph::printGraph(){
    for(int i = 0; i < numOfVertices; i++){
        if(adjList[i].isEmpty()){
            std::cout << "Vertex " << i+1 << " has no neighbors." << std::endl;
            continue;
        }

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