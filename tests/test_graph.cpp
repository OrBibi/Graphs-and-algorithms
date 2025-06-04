//orbibiariel@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/Algorithms.h"
#include "../src/Graph.h"
#include "../src/Vector.h"
#include <limits.h> 

using namespace graph;

// Constant to represent no edge from v to u
static const int NO_EDGE = INT_MIN;

// Test case for creating a graph and adding edges
TEST_CASE("Graph creation and adding edges") {
    Graph graph(5); // Create a graph with 5 nodes
    
    // Add edges with weights to the graph
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 3, 1);
    graph.addEdge(3, 4, 3);
    graph.addEdge(2, 1); // Add an edge with no weight (default weight = 1)

    // Check if the adjacency list reflects the added edges
    const int** adjList = graph.getAdjacencyList();
    CHECK(adjList[0][1] == 2);
    CHECK(adjList[0][2] == 4);
    CHECK(adjList[1][3] == 1);
    CHECK(adjList[3][4] == 3);
    CHECK(adjList[1][0] == 2);
    CHECK(adjList[2][0] == 4);
    CHECK(adjList[3][1] == 1);
    CHECK(adjList[4][3] == 3);
    CHECK(adjList[1][2] == 1); // Default weight for missing edge
    CHECK(adjList[4][4] == NO_EDGE); // No self-loop, should be NO_EDGE
    CHECK(adjList[0][3] == NO_EDGE); // No direct connection, should be NO_EDGE

    Graph copyGraph = graph; // Test copy constructor
    const int** copyAdjList = copyGraph.getAdjacencyList();
    CHECK(copyAdjList[0][1] == 2);
    CHECK(copyAdjList[0][2] == 4);  
    CHECK(copyAdjList[1][3] == 1);
    CHECK(copyAdjList[3][4] == 3);
    CHECK(copyAdjList[1][0] == 2);
    CHECK(copyAdjList[2][0] == 4);
    CHECK(copyAdjList[3][1] == 1);
    CHECK(copyAdjList[4][3] == 3);
    CHECK(copyAdjList[1][2] == 1); // Default weight for missing edge
    CHECK(copyAdjList[4][4] == NO_EDGE); // No self-loop, should be NO_EDGE
    CHECK(copyAdjList[0][3] == NO_EDGE); // No direct connection, should be NO_EDGE
}

// Test case for Breadth-First Search (BFS) algorithm on a connected graph
TEST_CASE("Testing BFS Algorithm - connected graph") {
    Graph graph(5);
    
    // Add edges with weights
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 4, 1);

    // Run BFS starting from node 0
    Graph distances = Algorithms::bfs(graph, 0);
    
    // Check if the BFS distances are correctly calculated
    CHECK(distances.getAdjacencyList()[0][1] == 1);
    CHECK(distances.getAdjacencyList()[0][2] == 2);
    CHECK(distances.getAdjacencyList()[0][3] == 3);
    CHECK(distances.getAdjacencyList()[0][4] == 4);
}

// Test case for BFS on a disconnected graph
TEST_CASE("Testing BFS Algorithm - disconnected graph") {
    Graph graph(5);
    
    // Add edges with weights
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 3, 1);

    // Run BFS starting from node 0
    Graph distances = Algorithms::bfs(graph, 0);
    
    // Check if the BFS distances are correctly calculated, and ensure unreachable nodes return NO_EDGE
    CHECK(distances.getAdjacencyList()[0][1] == 1);
    CHECK(distances.getAdjacencyList()[0][2] == 2);
    CHECK(distances.getAdjacencyList()[0][3] == 3);
    CHECK(distances.getAdjacencyList()[0][4] == NO_EDGE); // No connection to node 4
}

// Test case for Depth-First Search (DFS) algorithm
TEST_CASE("Testing DFS Algorithm") {
    Graph graph(5);
    
    // Add edges with weights
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 4, 1);

    // Run DFS starting from node 0
    Graph dfsGraph = Algorithms::dfs(graph, 0);
    
    // Check if the DFS traversal correctly reflects the graph's structure
    const int** adjList = dfsGraph.getAdjacencyList(); 
    CHECK(adjList[0][1] == 1);
    CHECK(adjList[1][2] == 1);
    CHECK(adjList[2][3] == 1);
    CHECK(adjList[3][4] == 1);
}

// Test case for Dijkstra's Algorithm
TEST_CASE("Testing Dijkstra's Algorithm") {
    Graph graph(5);
    
    // Add weighted edges to the graph
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 3, 9);

    // Run Dijkstra's algorithm starting from node 0
    Graph distances = Algorithms::dijkstra(graph, 0);
    
    // Check if the shortest paths are calculated correctly
    CHECK(distances.getAdjacencyList()[0][1] == 7);  // Shortest path from 0 to 1 is from node 2
    CHECK(distances.getAdjacencyList()[0][2] == 5);
    CHECK(distances.getAdjacencyList()[0][3] == 8);
}

// Test case for Prim's algorithm on a disconnected graph
TEST_CASE("Testing Prim's Algorithm - Disconnected Graph") {
    Graph graph(5);
    
    // Add weighted edges to the graph
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 9);

    // Check if an exception is thrown when Prim's algorithm is used on a disconnected graph
    bool exceptionThrown = false;
    try {
        Graph mstGraph = Algorithms::prim(graph, 0);
    } catch (const std::runtime_error& e) {
        exceptionThrown = true;
        CHECK(std::string(e.what()) == "Graph is disconnected, no MST can be formed.");
    }
    CHECK(exceptionThrown == true);
}

// Test case for Kruskal's algorithm on a disconnected graph
TEST_CASE("Testing Kruskal's Algorithm - Disconnected Graph") {
    Graph graph(5);
    
    // Add weighted edges to the graph
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 9);

    // Check if an exception is thrown when Kruskal's algorithm is used on a disconnected graph
    bool exceptionThrown = false;
    try {
        Graph mstGraph = Algorithms::kruskal(graph);
    } catch (const std::runtime_error& e) {
        exceptionThrown = true;
        CHECK(std::string(e.what()) == "Graph is disconnected, no MST can be formed.");
    }
    CHECK(exceptionThrown == true);
}

// Test case for Prim's algorithm on a graph with negative edges
TEST_CASE("Testing Prim's Algorithm - Negative edge") {
    Graph graph(5);
    
    // Add weighted edges, including negative edge weights
    graph.addEdge(0, 1, -5);
    graph.addEdge(0, 2, -2);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 3, 9);
    graph.addEdge(0, 4, 1);
    graph.addEdge(1, 4, 10);

    // Check if Prim's algorithm throws an exception when negative weights are present
    bool exceptionThrown = false;
    try {
        Graph mstGraph = Algorithms::prim(graph, 0);
    } catch (const std::runtime_error& e) {
        exceptionThrown = true;
        CHECK(std::string(e.what()) == "Graph contains negative edges, Prim's algorithm cannot be used.");
    }
    CHECK(exceptionThrown == true);
}

// Test case for Prim's algorithm on a connected graph
TEST_CASE("Testing Prim's Algorithm - Connected Graph") {
    Graph graph(5);
    
    // Add weighted edges to the graph
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 3, 9);
    graph.addEdge(0, 4, 1);
    graph.addEdge(1, 4, 10);

    // Run Prim's algorithm to find the minimum spanning tree (MST)
    Graph mstGraph = Algorithms::prim(graph, 0);
    
    const int** adjList = mstGraph.getAdjacencyList(); 
    CHECK(adjList[0][2] == 5);
    CHECK(adjList[1][2] == 2);
    CHECK(adjList[1][3] == 1);
    CHECK(adjList[0][4] == 1);
    CHECK(adjList[1][4] == NO_EDGE); // Edge not included in MST
}

// Test case for Kruskal's algorithm on a connected graph
TEST_CASE("Testing Kruskal's Algorithm - Connected Graph") {
    Graph graph(5);
    
    // Add weighted edges to the graph
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 3, 9);
    graph.addEdge(4, 3, 1);

    // Ensure the graph is connected before running Kruskal's algorithm
    Graph mstGraph = Algorithms::kruskal(graph);
    
    const int** adjList = mstGraph.getAdjacencyList();
    
    // Check if the edges in the MST are correct (minimum spanning tree)
    CHECK(adjList[0][2] == 5);
    CHECK(adjList[1][2] == 2);
    CHECK(adjList[1][3] == 1);
    CHECK(adjList[3][4] == 1);
    CHECK(adjList[2][3] == NO_EDGE); // Edge not included in MST
}
