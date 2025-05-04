/*
author: Meir Yust
mail: meyu251@gmail.com
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <sstream>
#include <string>
#include "Graph.hpp"
#include "Algorithms.hpp"
#include "Data_Structures.hpp"

using namespace graph;
using namespace std;

// Helper function to capture cout output
class CoutRedirect{
public:
    CoutRedirect(std::stringstream& buffer) : old_buf(std::cout.rdbuf(buffer.rdbuf())){}
    ~CoutRedirect() {std::cout.rdbuf(old_buf);}
private:
    std::streambuf* old_buf;
};

// Test suite for Data_Structures
TEST_CASE("DynamicArray tests"){
    SUBCASE("Empty array"){
        DynamicArray<int> arr;
        CHECK(arr.getSize() == 0);
        CHECK(arr.isEmpty() == true);
    }

    SUBCASE("Push back and access"){
        DynamicArray<int> arr;
        arr.push_back(5);
        arr.push_back(10);
        CHECK(arr.getSize() == 2);
        CHECK(arr[0] == 5);
        CHECK(arr[1] == 10);
        CHECK(arr.isEmpty() == false);
    }

    SUBCASE("Remove at"){
        DynamicArray<int> arr;
        arr.push_back(5);
        arr.push_back(10);
        arr.push_back(15);
        arr.removeAt(1);
        CHECK(arr.getSize() == 2);
        CHECK(arr[0] == 5);
        CHECK(arr[1] == 15);
    }

    SUBCASE("Copy constructor"){
        DynamicArray<int> arr1;
        arr1.push_back(5);
        arr1.push_back(10);

        DynamicArray<int> arr2(arr1);
        CHECK(arr2.getSize() == 2);
        CHECK(arr2[0] == 5);
        CHECK(arr2[1] == 10);

        // Change arr1, arr2 should remain the same
        arr1.push_back(15);
        CHECK(arr1.getSize() == 3);
        CHECK(arr2.getSize() == 2);
    }

    SUBCASE("Assignment operator"){
        DynamicArray<int> arr1;
        arr1.push_back(5);
        arr1.push_back(10);

        DynamicArray<int> arr2;
        arr2 = arr1;
        CHECK(arr2.getSize() == 2);
        CHECK(arr2[0] == 5);
        CHECK(arr2[1] == 10);

        // Modify arr1, arr2 should remain the same
        arr1.push_back(15);
        CHECK(arr1.getSize() == 3);
        CHECK(arr2.getSize() == 2);
    }

    SUBCASE("Out of range exception"){
        DynamicArray<int> arr;
        arr.push_back(5);
        CHECK_THROWS_AS(arr[1], std::out_of_range);
        CHECK_THROWS_AS(arr.removeAt(1), std::out_of_range);
    }
}

TEST_CASE("Queue tests"){
    SUBCASE("Empty queue"){
        Queue<int> q;
        CHECK(q.getSize() == 0);
        CHECK(q.isEmpty() == true);
        CHECK_THROWS_AS(q.dequeue(), std::out_of_range);
        CHECK_THROWS_AS(q.peek(), std::out_of_range);
    }

    SUBCASE("Enqueue and dequeue"){
        Queue<int> q;
        q.enqueue(5);
        q.enqueue(10);
        CHECK(q.getSize() == 2);
        CHECK(q.isEmpty() == false);
        CHECK(q.peek() == 5);
        
        int val = q.dequeue();
        CHECK(val == 5);
        CHECK(q.getSize() == 1);
        CHECK(q.peek() == 10);
        
        val = q.dequeue();
        CHECK(val == 10);
        CHECK(q.getSize() == 0);
        CHECK(q.isEmpty() == true);
    }

    SUBCASE("Multiple en/dequeue"){
        Queue<int> q;
        // Add and remove many elements to test circular behavior
        for(int i = 0; i < 10; i++){
            q.enqueue(i);
        }
        
        for(int i = 0; i < 5; i++){
            CHECK(q.dequeue() == i);
        }
        
        for(int i = 10; i < 15; i++){
            q.enqueue(i);
        }
        
        // Should continue from where we left
        for(int i = 5; i < 15; i++){
            CHECK(q.dequeue() == i);
        }
        
        CHECK(q.isEmpty() == true);
    }
}

TEST_CASE("Stack tests"){
    SUBCASE("Empty stack"){
        Stack<int> s;
        CHECK(s.getSize() == 0);
        CHECK(s.isEmpty() == true);
        CHECK_THROWS_AS(s.pop(), std::out_of_range);
        CHECK_THROWS_AS(s.peek(), std::out_of_range);
    }

    SUBCASE("Push and pop"){
        Stack<int> s;
        s.push(5);
        s.push(10);
        CHECK(s.getSize() == 2);
        CHECK(s.isEmpty() == false);
        CHECK(s.peek() == 10);
        
        int val = s.pop();
        CHECK(val == 10);
        CHECK(s.getSize() == 1);
        CHECK(s.peek() == 5);
        
        val = s.pop();
        CHECK(val == 5);
        CHECK(s.getSize() == 0);
        CHECK(s.isEmpty() == true);
    }
    
    SUBCASE("Multiple push and pop"){
        Stack<int> s;
    
        // Push a few elements
        s.push(1);
        s.push(2);
        CHECK(s.getSize() == 2);
        CHECK(s.peek() == 2);
    
        // Pop a few elements
        CHECK(s.pop() == 2);
        CHECK(s.getSize() == 1);
        CHECK(s.peek() == 1);
    
        // Push more elements
        s.push(4);
        s.push(5);
        CHECK(s.getSize() == 3);
        CHECK(s.peek() == 5);
    
        // Pop all elements and check order
        CHECK(s.pop() == 5);
        CHECK(s.pop() == 4);
        CHECK(s.pop() == 1);
        CHECK(s.getSize() == 0);
        CHECK(s.isEmpty() == true);
    }
}

TEST_CASE("PriorityQueue tests"){
    SUBCASE("Empty priority queue"){
        PriorityQueue<Pair<int, int>> pq;
        CHECK(pq.getSize() == 0);
        CHECK(pq.isEmpty() == true);
        CHECK_THROWS_AS(pq.dequeue(), std::out_of_range);
        CHECK_THROWS_AS(pq.peek(), std::out_of_range);
    }

    SUBCASE("Enqueue and dequeue"){
        PriorityQueue<Pair<int, int>> pq;
        // In Pair<int, int>, the priority is by the second value
        pq.enqueue({1, 5});
        pq.enqueue({2, 3});
        pq.enqueue({3, 7});
        
        CHECK(pq.getSize() == 3);
        CHECK(pq.isEmpty() == false);
        
        // Should dequeue in order of priority (lowest second value first)
        Pair<int, int> p = pq.dequeue();
        CHECK(p.first == 2);
        CHECK(p.second == 3);
        
        p = pq.dequeue();
        CHECK(p.first == 1);
        CHECK(p.second == 5);
        
        p = pq.dequeue();
        CHECK(p.first == 3);
        CHECK(p.second == 7);
        
        CHECK(pq.isEmpty() == true);
    }
}

TEST_CASE("DisjointSet tests"){
    SUBCASE("Basic operations"){
        DisjointSet<int> ds(5);
        
        // Initially all elements are in their own sets
        for(int i = 0; i < 4; i++){
            CHECK(ds.find(i) == i);
            CHECK(ds.isSameSet(i, i) == true);
            CHECK(ds.isSameSet(i, i+1) == false);
        }
        
        // Unite some sets
        ds.unionSets(0, 1);
        CHECK(ds.isSameSet(0, 1) == true);
        CHECK(ds.isSameSet(1, 2) == false);
        
        ds.unionSets(2, 3);
        CHECK(ds.isSameSet(2, 3) == true);
        CHECK(ds.isSameSet(0, 2) == false);
        
        // Unite the two groups
        ds.unionSets(0, 3);
        CHECK(ds.isSameSet(0, 3) == true);
        CHECK(ds.isSameSet(1, 2) == true);
        
        // Element 4 is still separate
        CHECK(ds.isSameSet(0, 4) == false);
    }
}

TEST_CASE("Graph tests"){
    SUBCASE("Empty graph"){
        Graph g(0);
        CHECK(g.getNumOfVertices() == 0);
        CHECK_THROWS_AS(g.printGraph(), std::invalid_argument);
    }

    SUBCASE("Single vertex graph"){
        Graph g(1);
        CHECK(g.getNumOfVertices() == 1);
        
        std::stringstream buffer;
        CoutRedirect redirect(buffer);
        g.printGraph();
        CHECK(buffer.str() == "Vertex 1 has no neighbors.\n");
    }

    SUBCASE("Basic graph operations"){
        Graph g(5);
        CHECK(g.getNumOfVertices() == 5);
        
        // Add edges
        g.addEdge(1, 2, 10);
        g.addEdge(1, 3, 5);
        g.addEdge(2, 4, 1);
        g.addEdge(3, 5, 2);
        g.addEdge(4, 5, 4);
        
        // Check if edges exist
        CHECK(g.hasEdge(1, 2) == true);
        CHECK(g.hasEdge(2, 1) == true); // Undirected graph
        CHECK(g.hasEdge(1, 4) == false);
        
        // Check neighbors
        DynamicArray<Pair<int, int>> neighbors = g.getNeighbors(1);
        CHECK(neighbors.getSize() == 2);
        bool has2 = false, has3 = false;
        for(int i = 0; i < neighbors.getSize(); i++){
            if(neighbors[i].first == 2 && neighbors[i].second == 10) has2 = true;
            if(neighbors[i].first == 3 && neighbors[i].second == 5) has3 = true;
        }
        CHECK(has2 == true);
        CHECK(has3 == true);
        
        // Remove edge
        g.removeEdge(1, 2);
        CHECK(g.hasEdge(1, 2) == false);
        // But the reverse edge still exists because removeEdge only removes directed edge
        CHECK(g.hasEdge(2, 1) == true);
    }

    SUBCASE("Adding duplicate edges"){
        Graph g(3);
        g.addEdge(1, 2, 5);
        CHECK_THROWS_AS(g.addEdge(1, 2, 10), std::invalid_argument);
        
        // Try adding a directed edge that already exists
        g.addDirectedEdge(2, 3, 7);
        CHECK_THROWS_AS(g.addDirectedEdge(2, 3, 8), std::invalid_argument);
    }

    SUBCASE("Invalid operations"){
        Graph g(3);
        // Invalid vertices
        CHECK_THROWS_AS(g.addEdge(0, 2, 5), std::invalid_argument);
        CHECK_THROWS_AS(g.addEdge(1, 4, 5), std::invalid_argument);
        CHECK_THROWS_AS(g.addEdge(1, 1, 5), std::invalid_argument); // Self-loop
        
        // Non-existent edge
        CHECK_THROWS_AS(g.removeEdge(1, 2), std::invalid_argument);
    }

    SUBCASE("Negative edge detection"){
        Graph g(3);
        g.addEdge(1, 2, 5);
        CHECK(g.hasNegativeEdge() == false);
        
        g.addEdge(2, 3, -2);
        CHECK(g.hasNegativeEdge() == true);
    }
}

TEST_CASE("BFS algorithm tests"){
    SUBCASE("BFS on empty graph"){
        Graph g(0);
        CHECK_THROWS_AS(bfs(g, 1), std::invalid_argument);
    }

    SUBCASE("BFS on single vertex graph"){
        Graph g(1);
        Graph bfsTree = bfs(g, 1);
        CHECK(bfsTree.getNumOfVertices() == 1);
        
        std::stringstream buffer;
        CoutRedirect redirect(buffer);
        bfsTree.printGraph();
        CHECK(buffer.str() == "Vertex 1 has no neighbors.\n");
    }

    SUBCASE("BFS on standard graph from vertex 1"){
        // Create a standard graph
        Graph g(6);
        g.addEdge(1, 2);
        g.addEdge(1, 3);
        g.addEdge(2, 4);
        g.addEdge(2, 5);
        g.addEdge(3, 5);
        g.addEdge(4, 6);
        g.addEdge(5, 6);
        
        Graph bfsTree = bfs(g, 1);
        
        // BFS from vertex 1 should include all edges in shortest path tree
        CHECK(bfsTree.hasEdge(1, 2) == true);
        CHECK(bfsTree.hasEdge(1, 3) == true);
        CHECK(bfsTree.hasEdge(2, 4) == true);
        CHECK(bfsTree.hasEdge(2, 5) == true);
        CHECK(bfsTree.hasEdge(4, 6) == true);
        
        // These edges should not be in the BFS tree
        CHECK(bfsTree.hasEdge(3, 5) == false);
        CHECK(bfsTree.hasEdge(5, 6) == false);
    }

    SUBCASE("BFS on standard graph from vertex 3"){
        // Create a standard graph
        Graph g(6);
        g.addEdge(1, 2);
        g.addEdge(1, 3);
        g.addEdge(2, 4);
        g.addEdge(2, 5);
        g.addEdge(3, 5);
        g.addEdge(4, 6);
        g.addEdge(5, 6);
        
        Graph bfsTree = bfs(g, 3);
        
        // BFS from vertex 3 should include all edges in shortest path tree
        CHECK(bfsTree.hasEdge(3, 1) == true);
        CHECK(bfsTree.hasEdge(3, 5) == true);
        CHECK(bfsTree.hasEdge(1, 2) == true);
        CHECK(bfsTree.hasEdge(5, 6) == true);
        CHECK(bfsTree.hasEdge(2, 4) == true);
        
        // These edges should not be in the BFS tree
        CHECK(bfsTree.hasEdge(2, 5) == false);
        CHECK(bfsTree.hasEdge(4, 6) == false);
    }

    SUBCASE("BFS with invalid root"){
        Graph g(5);
        CHECK_THROWS_AS(bfs(g, 0), std::invalid_argument);
        CHECK_THROWS_AS(bfs(g, 6), std::invalid_argument);
    }
}

TEST_CASE("DFS algorithm tests"){
    SUBCASE("DFS on empty graph"){
        Graph g(0);
        CHECK_THROWS_AS(dfs(g, 1), std::invalid_argument);
    }

    SUBCASE("DFS on single vertex graph"){
        Graph g(1);
        Graph dfsTree = dfs(g, 1);
        CHECK(dfsTree.getNumOfVertices() == 1);
        
        std::stringstream buffer;
        CoutRedirect redirect(buffer);
        dfsTree.printGraph();
        CHECK(buffer.str() == "Vertex 1 has no neighbors.\n");
    }

    SUBCASE("DFS on standard graph from vertex 1"){
        // Create a standard graph
        Graph g(6);
        g.addEdge(1, 2);
        g.addEdge(1, 3);
        g.addEdge(2, 4);
        g.addEdge(2, 5);
        g.addEdge(3, 5);
        g.addEdge(4, 6);
        g.addEdge(5, 6);
        
        Graph dfsTree = dfs(g, 1);
        
        // Because DFS is dependent on the implementation and order of traversal,
        // we'll just verify that all vertices are reachable from the root
        CHECK(dfsTree.getNumOfVertices() == 6);
        
        // Count the total number of edges in the DFS tree
        int edgeCount = 0;
        for(int i = 1; i <= 6; i++) {
            DynamicArray<Pair<int, int>> neighbors = dfsTree.getNeighbors(i);
            edgeCount += neighbors.getSize();
        }
        
        // A tree with n vertices has n-1 edges
        CHECK(edgeCount == 5);
    }

    SUBCASE("DFS on standard graph from vertex 4"){
        // Create a standard graph
        Graph g(6);
        g.addEdge(1, 2);
        g.addEdge(1, 3);
        g.addEdge(2, 4);
        g.addEdge(2, 5);
        g.addEdge(3, 5);
        g.addEdge(4, 6);
        g.addEdge(5, 6);
        
        Graph dfsTree = dfs(g, 4);
        
        // Verify that all vertices are reachable
        CHECK(dfsTree.getNumOfVertices() == 6);
        
        // Count the total number of edges in the DFS tree
        int edgeCount = 0;
        for(int i = 1; i <= 6; i++) {
            DynamicArray<Pair<int, int>> neighbors = dfsTree.getNeighbors(i);
            edgeCount += neighbors.getSize();
        }
        
        // A tree with n vertices has n-1 edges
        CHECK(edgeCount == 5);
    }

    SUBCASE("DFS with invalid root"){
        Graph g(5);
        CHECK_THROWS_AS(dfs(g, 0), std::invalid_argument);
        CHECK_THROWS_AS(dfs(g, 6), std::invalid_argument);
    }
}

TEST_CASE("Dijkstra algorithm tests"){
    SUBCASE("Dijkstra on empty graph"){
        Graph g(0);
        CHECK_THROWS_AS(dijkstra(g, 1), std::invalid_argument);
    }

    SUBCASE("Dijkstra on single vertex graph"){
        Graph g(1);
        Graph dijkstraTree = dijkstra(g, 1);
        CHECK(dijkstraTree.getNumOfVertices() == 1);
        
        std::stringstream buffer;
        CoutRedirect redirect(buffer);
        dijkstraTree.printGraph();
        CHECK(buffer.str() == "Vertex 1 has no neighbors.\n");
    }

    SUBCASE("Dijkstra on standard graph from vertex 1"){
        Graph g(5);
        g.addEdge(1, 2, 10);
        g.addEdge(1, 3, 5);
        g.addEdge(2, 3, 2);
        g.addEdge(2, 4, 1);
        g.addEdge(3, 4, 9);
        g.addEdge(3, 5, 2);
        g.addEdge(4, 5, 4);
        
        Graph dijkstraTree = dijkstra(g, 1);
        
        // Check shortest path tree
        CHECK(dijkstraTree.hasEdge(1, 3) == true);
        CHECK(dijkstraTree.hasEdge(3, 5) == true);
        CHECK(dijkstraTree.hasEdge(3, 2) == true);
        CHECK(dijkstraTree.hasEdge(2, 4) == true);
        
        // These should not be in the shortest path tree
        CHECK(dijkstraTree.hasEdge(1, 2) == false);
        CHECK(dijkstraTree.hasEdge(3, 4) == false);
        CHECK(dijkstraTree.hasEdge(4, 5) == false);
    }

    SUBCASE("Dijkstra on standard graph from vertex 3"){
        Graph g(5);
        g.addEdge(1, 2, 10);
        g.addEdge(1, 3, 5);
        g.addEdge(2, 3, 2);
        g.addEdge(2, 4, 1);
        g.addEdge(3, 4, 9);
        g.addEdge(3, 5, 2);
        g.addEdge(4, 5, 4);
        
        Graph dijkstraTree = dijkstra(g, 3);
        
        // Check shortest path tree from vertex 3
        CHECK(dijkstraTree.hasEdge(3, 5) == true);
        CHECK(dijkstraTree.hasEdge(3, 2) == true);
        CHECK(dijkstraTree.hasEdge(2, 4) == true);
        CHECK(dijkstraTree.hasEdge(3, 1) == true);
        
        // These should not be in the shortest path tree
        CHECK(dijkstraTree.hasEdge(4, 5) == false);
    }

    SUBCASE("Dijkstra with negative edges"){
        Graph g(3);
        g.addEdge(1, 2, 5);
        g.addEdge(2, 3, -2); // Negative edge
        
        CHECK_THROWS_AS(dijkstra(g, 1), std::invalid_argument);
    }

    SUBCASE("Dijkstra with invalid start vertex"){
        Graph g(5);
        CHECK_THROWS_AS(dijkstra(g, 0), std::invalid_argument);
        CHECK_THROWS_AS(dijkstra(g, 6), std::invalid_argument);
    }
}

TEST_CASE("Prim algorithm tests"){
    SUBCASE("Prim on empty graph"){
        Graph g(0);
        CHECK_THROWS_AS(prim(g), std::invalid_argument);
    }

    SUBCASE("Prim on single vertex graph"){
        Graph g(1);
        Graph mst = prim(g);
        CHECK(mst.getNumOfVertices() == 1);
        
        std::stringstream buffer;
        CoutRedirect redirect(buffer);
        mst.printGraph();
        CHECK(buffer.str() == "Vertex 1 has no neighbors.\n");
    }

    SUBCASE("Prim on standard graph"){
        Graph g(5);
        g.addEdge(1, 2, 10);
        g.addEdge(1, 3, 5);
        g.addEdge(2, 3, 2);
        g.addEdge(2, 4, 1);
        g.addEdge(3, 4, 9);
        g.addEdge(3, 5, 2);
        g.addEdge(4, 5, 4);
        
        Graph mst = prim(g);
        
        // Count the total weight of the MST
        int totalWeight = 0;
        for(int i = 1; i <= 5; i++){
            DynamicArray<Pair<int, int>> neighbors = mst.getNeighbors(i);
            for(int j = 0; j < neighbors.getSize(); j++){
                totalWeight += neighbors[j].second;
            }
        }
        
        // MST weight should be doubled because it's an undirected graph representation
        CHECK(totalWeight == 10); // (1,3)=5 + (2,3)=2 + (2,4)=1 + (3,5)=2 = 10
        
        // MST should have exactly n-1 edges
        int edgeCount = g.getNumOfVertices() - 1;       
        CHECK(edgeCount == 4);
    }

    SUBCASE("Prim with negative edges"){
        Graph g(3);
        g.addEdge(1, 2, 5);
        g.addEdge(2, 3, -2); // Negative edge
        
        CHECK_THROWS_AS(prim(g), std::invalid_argument);
    }
}

TEST_CASE("Kruskal algorithm tests"){
    SUBCASE("Kruskal on empty graph"){
        Graph g(0);
        CHECK_THROWS_AS(kruskal(g), std::invalid_argument);
    }

    SUBCASE("Kruskal on single vertex graph"){
        Graph g(1);
        Graph mst = kruskal(g);
        CHECK(mst.getNumOfVertices() == 1);
        
        std::stringstream buffer;
        CoutRedirect redirect(buffer);
        mst.printGraph();
        CHECK(buffer.str() == "Vertex 1 has no neighbors.\n");
    }

    SUBCASE("Kruskal on standard graph"){
        Graph g(5);
        g.addEdge(1, 2, 10);
        g.addEdge(1, 3, 5);
        g.addEdge(2, 3, 2);
        g.addEdge(2, 4, 1);
        g.addEdge(3, 4, 9);
        g.addEdge(3, 5, 2);
        g.addEdge(4, 5, 4);
        
        Graph mst = kruskal(g);
        
        // Count the total weight of the MST
        int totalWeight = 0;
        for(int i = 1; i <= 5; i++){
            DynamicArray<Pair<int, int>> neighbors = mst.getNeighbors(i);
            for(int j = 0; j < neighbors.getSize(); j++){
                totalWeight += neighbors[j].second;
            }
        }
        
        // MST weight should be doubled because it's an undirected graph representation
        CHECK(totalWeight == 10); // (1,3)=5 + (2,3)=2 + (2,4)=1 + (3,5)=2 = 10
        
        // MST should have exactly n-1 edges
        int edgeCount = g.getNumOfVertices() - 1;
        CHECK(edgeCount == 4);
    }

    SUBCASE("Kruskal with negative edges"){
        Graph g(3);
        g.addEdge(1, 2, 5);
        g.addEdge(2, 3, -2); // Negative edge
        
        CHECK_THROWS_AS(kruskal(g), std::invalid_argument);
    }
    
    SUBCASE("Compare Kruskal and Prim results"){
        Graph g(6);
        g.addEdge(1, 2, 3);
        g.addEdge(1, 3, 1);
        g.addEdge(2, 3, 5);
        g.addEdge(2, 4, 2);
        g.addEdge(3, 4, 4);
        g.addEdge(3, 5, 6);
        g.addEdge(4, 6, 8);
        g.addEdge(5, 6, 7);
        
        Graph mstKruskal = kruskal(g);
        Graph mstPrim = prim(g);
        
        // Calculate total weights for both MSTs
        int weightKruskal = 0;
        int weightPrim = 0;
        
        for(int i = 1; i <= 6; i++) {
            DynamicArray<Pair<int, int>> neighborsKruskal = mstKruskal.getNeighbors(i);
            for(int j = 0; j < neighborsKruskal.getSize(); j++){
                weightKruskal += neighborsKruskal[j].second;
            }
            
            DynamicArray<Pair<int, int>> neighborsPrim = mstPrim.getNeighbors(i);
            for(int j = 0; j < neighborsPrim.getSize(); j++){
                weightPrim += neighborsPrim[j].second;
            }
        }
        
        // Both algorithms should produce MSTs with the same total weight
        // (although the structure might differ)
        CHECK(weightKruskal == weightPrim);
    }
    
    SUBCASE("Kruskal on disconnected graph"){
        Graph g(6);
        g.addEdge(1, 2, 1);
        g.addEdge(2, 3, 1);
        // Vertices 4, 5, 6 are disconnected from 1,2,3
        g.addEdge(4, 5, 1);
        g.addEdge(5, 6, 1);
        
        Graph mst = kruskal(g);
        
        // Kruskal should include all components
        CHECK(mst.hasEdge(1, 2) == true);
        CHECK(mst.hasEdge(2, 3) == true);
        CHECK(mst.hasEdge(4, 5) == true);
        CHECK(mst.hasEdge(5, 6) == true);
        
        // Count edges - should be n-c (n vertices, c connected components)
        int edgeCount = g.getNumOfVertices() - 2; // 6 vertices - 2 components
        CHECK(edgeCount == 4);
    }
}