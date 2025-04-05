//orbibiariel@gmail.com
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Graph.h"
#include "Vector.h" // Include Vector class

namespace graph {

    class Algorithms {
    public:
        static Graph bfs(const Graph& graph, int start);
        static Graph dfs(const Graph& graph, int randomStart = -1);
        static Graph dijkstra(const Graph& graph, int start);
        static Graph prim(const Graph& graph, int start = -1);
        static Graph kruskal(const Graph& graph);
    };

} // namespace graph

#endif
