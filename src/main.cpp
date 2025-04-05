#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN  // This should only be here, not in the test file
#include "Graph.h"
#include "Algorithms.h"
#include <iostream>

int main() {
    // Create a sample graph
    graph::Graph g(5);  // Create a graph with 5 vertices

    // Add edges to the graph
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 20);
    g.addEdge(1, 3, 30);
    g.addEdge(2, 4, 40);

    g.printGraph();
    std::cout << "use dijkstra:" << std::endl;

    // Run Dijkstra's algorithm
    graph::Algorithms algo;
    try {
        auto distances = algo.dijkstra(g, 0);
        std::cout << "Distances from vertex 0:" << std::endl;
        for (int i = 1; i < g.getNumVertices(); i++) {
            std::cout << "Vertex " << i << ": " << distances.getAdjacencyList()[0][i] << std::endl;
        }
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
