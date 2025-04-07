/*
author: Meir Yust
mail: meyu251@gmail.com
*/

#include <iostream>
#include "Graph.hpp"
#include "Data_Structures.hpp"

using namespace graph;

Graph::Graph(int n){
    adjList = new DynamicArray<Pair<int, int>>[n];  // first = neighbore, second = weight
    this->numOfVertices = n;
}

// copy constructor
Graph::Graph(const Graph& g){
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

Graph& Graph::operator=(const Graph& other){
    if(this != &other){
        delete[] adjList;
        numOfVertices = other.numOfVertices;
        adjList = new DynamicArray<Pair<int, int>>[numOfVertices];
        for(int i = 0; i < numOfVertices; i++){
            for(int j = 0; j < other.adjList[i].getSize(); j++){
                adjList[i].push_back(other.adjList[i].get(j));
            }
        }
    }
    return *this;
}

int Graph::getNumOfVertices(){
    return numOfVertices;
}

/*
Add an undirected edge between src and dest
-does not support an edge from a vertex to itself
-if the edge already exists, throw an exception
-if the edge exist only in one direction, add it in the other direction
-if the edge does not exist, add it in both directions
*/
void Graph::addEdge(int src, int dest, int weight){
    if(src < 1 || src > numOfVertices || dest < 1 || dest > numOfVertices || src == dest){
        throw std::invalid_argument("Invalid edge.");
    }

    // check if any of the edges already exists
    bool srcEdge = false;
    bool destEdge = false;
    for(int i = 0; i < adjList[src - 1].getSize(); i++){
        if(adjList[src - 1].get(i).first == dest){
            srcEdge = true;
            break;
        }
    }
    for(int i = 0; i < adjList[dest - 1].getSize(); i++){
        if(adjList[dest - 1].get(i).first == src){
            destEdge = true;
            break;
        }
    }

    if(srcEdge && destEdge){
        throw std::invalid_argument("Edge already exists.");
    }
    else if(srcEdge){
        std::cout << "Edge from " << src << " to " << dest << " already exists." << std::endl;
        adjList[dest - 1].push_back({src, weight});
    }
    else if(destEdge){
        std::cout << "Edge from " << dest << " to " << src << " already exists." << std::endl;
        adjList[src - 1].push_back({dest, weight});
    }
    else{
        adjList[src - 1].push_back({dest, weight});
        adjList[dest - 1].push_back({src, weight});
    }
}

/*
Add an undirected edge between src and dest with weight 1
- act as the function above
*/
void Graph::addEdge(int src, int dest){
    if(src < 1 || src > numOfVertices || dest < 1 || dest > numOfVertices || src == dest){
        throw std::invalid_argument("Invalid edge.");
    }

    // Check if any of the edges already exists
    bool srcEdge = false;
    bool destEdge = false;
    for(int i = 0; i < adjList[src - 1].getSize(); i++){
        if(adjList[src - 1].get(i).first == dest){
            srcEdge = true;
            break;
        }
    }
    for(int i = 0; i < adjList[dest - 1].getSize(); i++){
        if(adjList[dest - 1].get(i).first == src){
            destEdge = true;
            break;
        }
    }

    if(srcEdge && destEdge){
        throw std::invalid_argument("Edge already exists.");
    }
    else if(srcEdge){
        std::cout << "Edge from " << src << " to " << dest << " already exists." << std::endl;
        adjList[dest - 1].push_back({src, 1});
    }
    else if(destEdge){
        std::cout << "Edge from " << dest << " to " << src << " already exists." << std::endl;
        adjList[src - 1].push_back({dest, 1});
    }
    else{
        adjList[src - 1].push_back({dest, 1});
        adjList[dest - 1].push_back({src, 1});
    }
}

void Graph::addDirectedEdge(int src, int dest, int weight){
    if(src < 1 || src > numOfVertices || dest < 1 || dest > numOfVertices || src == dest){
        throw std::invalid_argument("Invalid edge.");
    }

    // check if the edge already exists
    for(int i = 0; i < adjList[src - 1].getSize(); i++){
        if(adjList[src - 1].get(i).first == dest){
            throw std::invalid_argument("Edge already exists.");
        }
    }

    adjList[src - 1].push_back({dest, weight});
}

void Graph::addDirectedEdge(int src, int dest){
    if(src < 1 || src > numOfVertices || dest < 1 || dest > numOfVertices || src == dest){
        throw std::invalid_argument("Invalid edge.");
    }

    // check if the edge already exists
    for(int i = 0; i < adjList[src - 1].getSize(); i++){
        if(adjList[src - 1].get(i).first == dest){
            throw std::invalid_argument("Edge already exists.");
        }
    }

    adjList[src - 1].push_back({dest, 1});
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
Remove a directed edge between src and dest
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
    
    // remove the edge from dest to src

    // for(int i = 0; i < adjList[dest - 1].getSize(); i++){
    //     if(adjList[dest - 1].get(i).first == src){
    //         adjList[dest - 1].removeAt(i);
    //         break;
    //     }
    // }
}

/*
Print the graph in the following format:
{vertex1->neighbor (weight)}, {vertex1->neighbor (weight)}, ...
{vertex2->neighbor (weight)}, {vertex2->neighbor (weight)}, ...
.
.
.
{vertexN->neighbor (weight)}, {vertexN->neighbor (weight)}, ..

if there are no edeges for a vertex, print "Vertex i has no neighbors."
*/
void Graph::printGraph(){
    if(numOfVertices == 0){
        throw std::invalid_argument("Graph is empty.");
    }

    for(int i = 0; i < numOfVertices; i++){
        if(adjList[i].isEmpty()){
            std::cout << "Vertex " << i+1 << " has no neighbors." << std::endl;
            continue;
        }

        for(int j = 0; j < adjList[i].getSize(); j++){
            std::cout << "{" << i+1 << "->" << adjList[i].get(j).first << " (" << adjList[i].get(j).second << ")}";
            if(j != adjList[i].getSize() - 1){
                std::cout << ", ";
            }
            else{
                std::cout << std::endl;
            }
        }
    }
}

DynamicArray<Pair<int, int>> Graph::getNeighbors(int vertex){
    return adjList[vertex - 1];
}

bool Graph::hasNegativeEdge(){
    for(int i = 0; i < numOfVertices; i++){
        DynamicArray<Pair<int, int>> neighbors = getNeighbors(i + 1);
        for(int j = 0; j < neighbors.getSize(); j++){
            if(neighbors[j].second < 0){
                return true;
            }
        }
    }
    return false;
}