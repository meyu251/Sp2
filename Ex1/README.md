# Graph Algorithms Project

## Author
Meir Yust (meyu251@gmail.com)

## Overview
This project implements a suite of graph algorithms and necessary data structures in C++. It features a flexible Graph class and efficient implementations of common graph traversal and minimum spanning tree algorithms.

## Project Structure

### Core Components

1. **Graph Class** (within `graph` namespace):
   - A flexible implementation of a graph data structure with adjacency list representation
   - Supports both directed and undirected edges with weights
   - Vertices are numbered from 1 to n for intuitive use
   - Includes proper constructors, destructors, and assignment operators for memory management

2. **Data Structures** (within `graph` namespace):
   - Custom implementation of fundamental data structures required for graph algorithms:
     - Dynamic Array: A resizable array implementation with proper resource management
     - Pair: A simple key-value container
     - Queue: For breadth-first traversal
     - Stack: For depth-first traversal
     - Priority Queue: For Dijkstra's and Prim's algorithms
     - Disjoint Set: For Kruskal's algorithm

3. **Graph Algorithms** (within `graph` namespace):
   - Traversal algorithms:
     - Breadth-First Search (BFS)
     - Depth-First Search (DFS)
   - Shortest path algorithm:
     - Dijkstra's algorithm
   - Minimum Spanning Tree algorithms:
     - Prim's algorithm
     - Kruskal's algorithm

4. **Testing Framework**:
   - Comprehensive tests using doctest for all data structures and algorithms

## Classes and Functions

### Graph.hpp / Graph.cpp

The `Graph` class provides the core graph functionality:

- **Constructor**: 
  - `Graph(int n)`: Creates a graph with n vertices

- **Graph Operations**:
  - `getNumOfVertices()`: Returns the number of vertices
  - `addEdge(int src, int dest, int weight)`: Adds an undirected edge with weight
  - `addEdge(int src, int dest)`: Adds an undirected edge with default weight 1
  - `addDirectedEdge(int src, int dest, int weight)`: Adds a directed edge with weight
  - `addDirectedEdge(int src, int dest)`: Adds a directed edge with default weight 1
  - `hasEdge(int src, int dest)`: Checks if an edge exists
  - `removeEdge(int src, int dest)`: Removes a directed edge
  - `printGraph()`: Outputs a text representation of the graph
  - `getNeighbors(int vertex)`: Returns all neighbors of a vertex
  - `hasNegativeEdge()`: Checks if the graph contains any negative weight edges

### Data_Structures.hpp

Contains implementations of several key data structures needed for graph algorithms:

1. **DynamicArray<T>**:
   - A templated, resizable array implementation
   - Key methods: `push_back()`, `removeAt()`, `get()`, `operator[]`

2. **Pair<T1, T2>**:
   - A simple key-value pair structure
   - Used for representing edges and their weights

3. **Queue<T>**:
   - A FIFO queue implementation
   - Key methods: `enqueue()`, `dequeue()`, `peek()`, `isEmpty()`
   - Used in BFS algorithm

4. **Stack<T>**:
   - A LIFO stack implementation
   - Key methods: `push()`, `pop()`, `peek()`, `isEmpty()`
   - Used in DFS algorithm

5. **PriorityQueue<T>**:
   - A min-heap implementation
   - Key methods: `enqueue()`, `dequeue()`, `peek()`, `isEmpty()`
   - Used in Dijkstra's and Prim's algorithms

6. **DisjointSet<T>**:
   - An efficient union-find data structure with path compression and union by rank
   - Key methods: `find()`, `unionSets()`, `isSameSet()`
   - Used in Kruskal's algorithm

### Algorithms.hpp / Algorithms.cpp

Implements several graph algorithms within the `graph` namespace:

1. **BFS** - `Graph bfs(Graph& g, int root)`:
   - Performs breadth-first search from a given root vertex
   - Returns a new graph representing the BFS tree

2. **DFS** - `Graph dfs(Graph& g, int root)`:
   - Performs depth-first search from a given root vertex
   - Returns a new graph representing the DFS tree

3. **Dijkstra** - `Graph dijkstra(Graph& g, int startVertex)`:
   - Implements Dijkstra's algorithm for finding shortest paths
   - Returns a graph representing the shortest path tree
   - Throws an exception if the graph contains negative edges

4. **Prim** - `Graph prim(Graph& g)`:
   - Implements Prim's algorithm for finding minimum spanning tree
   - Returns a graph representing the MST
   - Throws an exception if the graph contains negative edges

5. **Kruskal** - `Graph kruskal(Graph& g)`:
   - Implements Kruskal's algorithm for finding minimum spanning tree
   - Returns a graph representing the MST
   - Uses quicksort to sort edges by weight
   - Throws an exception if the graph contains negative edges

## Example Usage

The `main.cpp` file demonstrates how to use the project:

```cpp
#include <iostream>
#include "Algorithms.hpp"

using namespace std;
using namespace graph;  // Using the graph namespace

int main() {
    // Create a graph with 5 vertices
    Graph g(5);
    
    // Add edges with weights
    g.addEdge(1, 2, 10);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 2);
    g.addEdge(2, 4, 1);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 2);
    g.addEdge(4, 5, 4);

    // Print the original graph
    cout << "Original Graph:" << endl;
    g.printGraph();
    
    // Run BFS from vertex 3
    Graph bfsResult = bfs(g, 3);
    cout << "BFS Result:" << endl;
    bfsResult.printGraph();
    
    // Run DFS from vertex 1
    Graph dfsResult = dfs(g, 1);
    cout << "DFS Result:" << endl;
    dfsResult.printGraph();
    
    // Find shortest paths using Dijkstra's algorithm
    Graph dijkstraResult = dijkstra(g, 1);
    cout << "Dijkstra Result:" << endl;
    dijkstraResult.printGraph();
    
    // Find MST using Prim's algorithm
    Graph primResult = prim(g);
    cout << "Prim Result:" << endl;
    primResult.printGraph();
    
    // Find MST using Kruskal's algorithm
    Graph kruskalResult = kruskal(g);
    cout << "Kruskal Result:" << endl;
    kruskalResult.printGraph();
    
    return 0;
}
```

## Testing

The project includes comprehensive tests in `test_main.cpp` using the doctest framework. Tests cover:

- Basic data structure functionality
- Graph operations
- BFS and DFS traversal
- Dijkstra's shortest path algorithm
- Prim's and Kruskal's MST algorithms

To run the tests, compile and execute the `test_main.cpp` file.

## Implementation Details

### Namespace

The entire project is encapsulated within the `graph` namespace as per project requirements. This provides proper code organization and prevents naming conflicts. All classes, functions, and algorithms are accessed via this namespace:

```cpp
// Example of using classes and algorithms via the namespace
graph::Graph g(5);
graph::Graph bfsResult = graph::bfs(g, 1);
```

### Object-Oriented Design

The project follows proper object-oriented design principles:

1. **Constructors and Destructors**:
   - Each class has appropriate constructors, including default and parameterized constructors
   - Proper destructors are implemented to handle resource cleanup (like dynamic memory)
   - Copy constructors are implemented where needed to handle deep copying

2. **Resource Management**:
   - All dynamically allocated memory is properly freed in destructors
   - Classes that manage resources (like DynamicArray) implement the Rule of Three:
     - Custom copy constructor
     - Custom destructor
     - Custom assignment operator

3. **Encapsulation**:
   - Private member variables with public accessor methods
   - Implementation details are hidden from the user

4. **Error Handling**:
   - Proper validation of inputs
   - Appropriate exceptions are thrown when invalid operations are attempted

## Building the Project

The project includes a Makefile for easy compilation. You'll need:
- A C++ compiler with C++17 support (default is clang++)
- make utility

### Using the Makefile

The Makefile provides several targets:

```bash
# Build both main and test executables
make all

# Build and run the main program
make Main

# Build and run the test program
make test

# Run valgrind memory check on the main program
make valgrind

# Clean up compiled files
make clean
```

### Compilation Details

The Makefile uses the following compilation flags:
- `-std=c++17`: Use C++17 standard
- `-Wall -Wextra -pedantic`: Enable comprehensive warnings

If you want to build manually without the Makefile:

```bash
# Main program
clang++ -std=c++17 -Wall -Wextra -pedantic main.cpp Graph.cpp Algorithms.cpp -o main_exec

# Test program
clang++ -std=c++17 -Wall -Wextra -pedantic test_main.cpp Graph.cpp Algorithms.cpp -o test_exec
```

Note: While the default compiler is clang++, the project should work with any modern C++ compiler that supports C++17 or newer. You can change the compiler in the Makefile by modifying the `CXX` variable.