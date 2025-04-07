/*
author: Meir Yust
mail: meyu251@gmail.com
*/

#pragma once

#include <iostream>
#include "Graph.hpp"

namespace graph{

    Graph bfs(Graph& g, int startVertex);
    Graph dfs(Graph& g, int startVertex);
    Graph dijkstra(Graph& g, int startVertex);
    Graph prim(Graph& g);
    Graph kruskal(Graph& g);

}