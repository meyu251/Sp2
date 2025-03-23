#include "Graph.hpp"

namespace graph {

// מימוש המחלקה Graph

Graph::Graph(int n) {
    vertices = n;
    adjacencyList = new DynamicArray[vertices];
}

Graph::~Graph() {
    delete[] adjacencyList;
}

void Graph::addEdge(int u, int v) {
    if (u >= 0 && u < vertices && v >= 0 && v < vertices) {
        if (!adjacencyList[u].contains(v)) {
            adjacencyList[u].push_back(v);
        }
        
        if (!adjacencyList[v].contains(u)) {
            adjacencyList[v].push_back(u);
        }
    }
}

void Graph::removeEdge(int u, int v) {
    if (u >= 0 && u < vertices && v >= 0 && v < vertices) {
        adjacencyList[u].remove(v);
        adjacencyList[v].remove(u);
    }
}

bool Graph::hasEdge(int u, int v) const {
    if (u >= 0 && u < vertices && v >= 0 && v < vertices) {
        return adjacencyList[u].contains(v);
    }
    return false;
}

int Graph::getNumVertices() const {
    return vertices;
}

void Graph::printGraph() const {
    for (int i = 0; i < vertices; i++) {
        std::cout << "Vertex " << i << " is connected to: ";
        for (int j = 0; j < adjacencyList[i].getSize(); j++) {
            std::cout << adjacencyList[i].at(j) << " ";
        }
        std::cout << std::endl;
    }
}

int Graph::getNumNeighbors(int v) const {
    if (v >= 0 && v < vertices) {
        return adjacencyList[v].getSize();
    }
    return 0;
}

int Graph::getNeighbor(int v, int i) const {
    if (v >= 0 && v < vertices && i >= 0 && i < adjacencyList[v].getSize()) {
        return adjacencyList[v].at(i);
    }
    return -1;
}

bool Graph::hasPath(int u, int v) const {
    if (u >= 0 && u < vertices && v >= 0 && v < vertices) {
        // אם זה אותו קודקוד, יש מסלול טריוויאלי
        if (u == v) {
            return true;
        }
        
        // שימוש ב-BFS כדי למצוא מסלול
        bool* visited = new bool[vertices];
        for (int i = 0; i < vertices; i++) {
            visited[i] = false;
        }
        
        // יצירת תור עם קיבולת מספיקה
        Queue queue(vertices);
        
        // מסמן את הקודקוד ההתחלתי כמבוקר ומכניס אותו לתור
        visited[u] = true;
        queue.enqueue(u);
        
        // לולאת BFS
        while (!queue.isEmpty()) {
            int currentVertex = queue.dequeue();
            
            // בדיקה של כל השכנים
            for (int i = 0; i < adjacencyList[currentVertex].getSize(); i++) {
                int adjVertex = adjacencyList[currentVertex].at(i);
                
                // אם מצאנו את היעד, יש מסלול
                if (adjVertex == v) {
                    delete[] visited;
                    return true;
                }
                
                // אם השכן לא בוקר, מסמן אותו כמבוקר ומכניס לתור
                if (!visited[adjVertex]) {
                    visited[adjVertex] = true;
                    queue.enqueue(adjVertex);
                }
            }
        }
        
        delete[] visited;
    }
    
    return false;
}

}  // namespace graph