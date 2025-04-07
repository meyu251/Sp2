/*
author: Meir Yust
mail: meyu251@gmail.com
*/

#include <iostream>
#include <climits>
#include "Graph.hpp"
#include "Algorithms.hpp"

using namespace std;

namespace graph{

Graph bfs(Graph& g, int root){
    if(root < 1 || root > g.getNumOfVertices()){
        throw std::invalid_argument("Invalid root.");
    }

    Graph ans(g.getNumOfVertices());
    DynamicArray<bool> visited(g.getNumOfVertices());
    for(int i = 0; i < g.getNumOfVertices(); i++){
        visited.push_back(false);
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
                ans.addDirectedEdge(current, neighbor, neighbors[i].second);    // add also the original weight of this edge
            }
        }
    }

    return ans;
}

Graph dfs(Graph& g, int root){
    if(root < 1 || root > g.getNumOfVertices()){
        throw std::invalid_argument("Invalid root.");
    }

    Graph ans(g.getNumOfVertices());
    DynamicArray<int> visited(g.getNumOfVertices()); // consider 0 as not visited, 1 as visited but not finished, 2 as visited and finished
    for(int i = 0; i < g.getNumOfVertices(); i++){
        visited.push_back(0);
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
            if(visited[neighbor - 1] == 0){     // only if not visited at all
                s.push(neighbor);
                visited[neighbor - 1] = 1;
                ans.addDirectedEdge(current, neighbor, neighbors[i].second);    // add also the original weight of this edge
                allVisited = false;
                break;
            }
        }
        if(allVisited){     // all neighbors are visited so we can finish this vertex
            visited[current - 1] = 2;
            s.pop();
        }
    }

    return ans;
}

Graph dijkstra(Graph& g, int startVertex){
    if(g.hasNegativeEdge()){
        throw std::invalid_argument("Dijkstra's algorithm cannot handle graphs with negative edge weights.");
    }
    if(startVertex < 1 || startVertex > g.getNumOfVertices()){
        throw std::invalid_argument("Invalid starting vertex.");
    }

    Graph ans(g.getNumOfVertices());
    DynamicArray<int> dist(g.getNumOfVertices());
    DynamicArray<bool> visited(g.getNumOfVertices());
    DynamicArray<int> parents(g.getNumOfVertices());
    for(int i = 0; i < g.getNumOfVertices(); i++){
        dist.push_back(INT_MAX);
        visited.push_back(false);
        parents.push_back(-1);   // -1 means no parent
    }

    dist[startVertex - 1] = 0;   // the -1 is becouse the vertex numbered from 1 to n and the array from 0 to n-1
    PriorityQueue<Pair<int, int>> pq;   // the first is the vertex and the second is the distance
    pq.enqueue({startVertex, 0});

    while(!pq.isEmpty()){
        Pair<int, int> current = pq.peek();
        pq.dequeue();
        int currentVertex = current.first;
        int currentDist = current.second;  
        if(visited[currentVertex - 1]) continue; // already visited
        visited[currentVertex - 1] = true;

        DynamicArray<Pair<int, int>> neighbors = g.getNeighbors(currentVertex);
        for(int i = 0; i < neighbors.getSize(); i++){
            int neighbor = neighbors[i].first;
            int weight = neighbors[i].second;
            
            if(!visited[neighbor - 1] && dist[currentVertex - 1] + weight < dist[neighbor - 1]){
                dist[neighbor - 1] = dist[currentVertex - 1] + weight;
                parents[neighbor - 1] = currentVertex;
                pq.enqueue({neighbor, dist[neighbor - 1]});
            }
        }
    }
    // build the ans graph

    while(!pq.isEmpty()){
        Pair<int, int> current = pq.peek();
        pq.dequeue();
        int currentVertex = current.first;
        int currentDist = current.second;  
        if(visited[currentVertex - 1]) continue; // already visited
        visited[currentVertex - 1] = true;

        DynamicArray<Pair<int, int>> neighbors = g.getNeighbors(currentVertex);
        for(int i = 0; i < neighbors.getSize(); i++){
            int neighbor = neighbors[i].first;
            int weight = neighbors[i].second;
            
            if(!visited[neighbor - 1] && dist[currentVertex - 1] + weight < dist[neighbor - 1]){
                dist[neighbor - 1] = dist[currentVertex - 1] + weight;
                parents[neighbor - 1] = currentVertex;
                pq.enqueue({neighbor, dist[neighbor - 1]});
            }
        }
    }

    // build the ans graph
    for(int i = 0; i < parents.getSize(); i++){
        if(parents[i] != -1){   // if there is a parent
            int vertex = i + 1;
            int parent = parents[i];
            DynamicArray<Pair<int, int>> neighbors = g.getNeighbors(parent);
            for(int j = 0; j < neighbors.getSize(); j++){
                if(neighbors[j].first == vertex){   // find the weight of the edge
                    ans.addDirectedEdge(parent, vertex, neighbors[j].second);
                    break;
                }
            }
        }
    }

    return ans;
}

Graph prim(Graph& g){
    if(g.hasNegativeEdge()){
        throw std::invalid_argument("Prim's algorithm cannot handle graphs with negative edge weights.");
    }

    Graph mst(g.getNumOfVertices());    // this is the ans Graph
    DynamicArray<bool> inMST(g.getNumOfVertices());
    DynamicArray<int> key(g.getNumOfVertices());
    DynamicArray<int> parents(g.getNumOfVertices());

    for(int i = 0; i < g.getNumOfVertices(); i++){
        inMST.push_back(false);
        key.push_back(INT_MAX);
        parents.push_back(-1);   // -1 means no parent
    }
    
    PriorityQueue<Pair<int, int>> pq; // first = vertex, second = key
    
    // We start from vertex 1
    key[0] = 0;
    pq.enqueue({1, 0});
    
    while(!pq.isEmpty()){
        Pair<int, int> current = pq.dequeue();
        int currentVertex = current.first;
        
        if(inMST[currentVertex - 1]) continue;
        inMST[currentVertex - 1] = true;
        
        // Add this vertex to the MST (if it's not the starting vertex)
        if(parents[currentVertex - 1] != -1){
            // Find the original weight from the graph
            DynamicArray<Pair<int, int>> neighbors = g.getNeighbors(parents[currentVertex - 1]);
            for(int i = 0; i < neighbors.getSize(); i++){
                if(neighbors[i].first == currentVertex){
                    mst.addDirectedEdge(parents[currentVertex - 1], currentVertex, neighbors[i].second);
                    break;
                }
            }
        }
        
        // Explore neighbors
        DynamicArray<Pair<int, int>> neighbors = g.getNeighbors(currentVertex);
        for(int i = 0; i < neighbors.getSize(); i++){
            int v = neighbors[i].first;
            int weight = neighbors[i].second;
            
            if(!inMST[v - 1] && weight < key[v - 1]){
                parents[v - 1] = currentVertex;
                key[v - 1] = weight;
                pq.enqueue({v, weight});
            }
        }
    }
    
    return mst;
}

// Helper function for quicksort
template <typename T>
int partition(DynamicArray<T>& arr, int low, int high){
    T pivot = arr[high];
    int i = low - 1;    // Index of smaller element
    
    for(int j = low; j < high; j++){
        // If current element is smaller than the pivot
        if(arr[j].second < pivot.second){
            i++;
            // Swap arr[i] and arr[j]
            T temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    // Swap arr[i+1] and arr[high] (pivot)
    T temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return i + 1;
}

// Recursive quicksort implementation
template <typename T>
void quickSort(DynamicArray<T>& arr, int low, int high){
    if(low < high){
        // pi is partitioning index
        int pi = partition(arr, low, high);
        
        // Sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

Graph kruskal(Graph& g){
    if(g.hasNegativeEdge()){
        throw std::invalid_argument("Kruskal's algorithm cannot handle graphs with negative edge weights.");
    }

    int numVertices = g.getNumOfVertices();
    if(numVertices == 0){
        throw std::invalid_argument("The graph is empty.");
    }
    
    Graph mst(numVertices);
    
    // Create a dynamic array to store all edges as: ((src, dest), weight)
    DynamicArray<Pair<Pair<int, int>, int>> edges;
    
    // Collect all edges from the graph
    for(int i = 1; i <= numVertices; i++){
        DynamicArray<Pair<int, int>> neighbors = g.getNeighbors(i);
        for(int j = 0; j < neighbors.getSize(); j++){
            int neighbor = neighbors[j].first;
            int weight = neighbors[j].second;
            
            // To consider each edge only once (when i < neighbor)
            if(i < neighbor){
                Pair<int, int> edge(i, neighbor);
                Pair<Pair<int, int>, int> weightedEdge(edge, weight);
                edges.push_back(weightedEdge);
            }
        }
    }
    
    // Sort edges by weight using quicksort
    if(edges.getSize() > 0){
        quickSort(edges, 0, edges.getSize() - 1);
    }
    
    // Create a disjoint set
    DisjointSet<int> ds(numVertices + 1);  // +1 because vertices are 1-indexed
    
    // Process edges in order of increasing weight
    for(int i = 0; i < edges.getSize(); i++){
        int src = edges[i].first.first;
        int dest = edges[i].first.second;
        int weight = edges[i].second;
        
        // Check if adding this edge creates a cycle
        if(!ds.isSameSet(src, dest)){
            // Add the edge to MST
            mst.addDirectedEdge(src, dest, weight);
            
            // Union the sets
            ds.unionSets(src, dest);
        }
    }
    
    return mst;
}

} // namespace graph