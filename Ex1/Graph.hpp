#pragma once

#include <iostream>
#include "Data_Structures.hpp"

namespace graph {

    // הצהרה על מחלקת Graph לייצוג גרף באמצעות רשימת שכנויות
    class Graph {
    private:
        DynamicArray* adjacencyList;  // מערך של מערכים דינמיים - כל אחד מייצג רשימת שכנים
        int vertices;                  // מספר הקודקודים בגרף

    public:
        // בנאי - מקבל את מספר הקודקודים
        Graph(int n);
        
        // הרס
        ~Graph();
        
        // הוספת קשת לגרף (גרף לא מכוון)
        void addEdge(int u, int v);
        
        // הסרת קשת מהגרף
        void removeEdge(int u, int v);
        
        // בדיקה האם קיימת קשת בין שני קודקודים
        bool hasEdge(int u, int v) const;
        
        // החזרת מספר הקודקודים בגרף
        int getNumVertices() const;
        
        // הדפסת הגרף
        void printGraph() const;
        
        // החזרת מספר השכנים של קודקוד
        int getNumNeighbors(int v) const;
        
        // החזרת השכן ה-i של קודקוד מסוים
        int getNeighbor(int v, int i) const;
        
        // בדיקה האם קיים מסלול בין שני קודקודים
        bool hasPath(int u, int v) const;
    };

}  // namespace graph