//orbibiariel@gmail.com
#include "Graph.h"
#include <iostream>
#include <stdexcept>

namespace graph {

    // Constructor
    Graph::Graph(int numVertices) {
        this->numVertices = numVertices;
        adjacencyList = new int*[numVertices];
        for (int i = 0; i < numVertices; i++) {
            adjacencyList[i] = new int[numVertices];
            // Initialize with NO_EDGE to represent no edge
            for (int j = 0; j < numVertices; j++) {
                adjacencyList[i][j] = NO_EDGE;  // No edge between vertices
            }
        }
        this->numOfNegativeEdges = 0;
    }

    // Copy Constructor
    Graph::Graph(const Graph& other) {
        this->numVertices = other.numVertices;
        this->numOfNegativeEdges = other.numOfNegativeEdges;

        // Allocate new memory for the adjacency list
        adjacencyList = new int*[numVertices];
        for (int i = 0; i < numVertices; i++) {
            adjacencyList[i] = new int[numVertices];
            for (int j = 0; j < numVertices; j++) {
                adjacencyList[i][j] = other.adjacencyList[i][j];
            }
        }
    }


    // Add edge
    void Graph::addEdge(int src, int dest, int weight) {
        if (src >= numVertices || dest >= numVertices || src < 0 || dest < 0) {
            throw std::out_of_range("Index out of range");
        }
        if (src==dest){
            throw std::out_of_range("No edges from v to himself");
        }
        adjacencyList[src][dest] = weight;
        adjacencyList[dest][src] = weight;

        if (weight < 0) numOfNegativeEdges++;  // Count negative edges
    }

    // Remove edge
    void Graph::removeEdge(int src, int dest) {
        if (src >= numVertices || dest >= numVertices || src < 0 || dest < 0) {
            throw std::out_of_range("Index out of range");
        }
        if (adjacencyList[src][dest] == NO_EDGE) {
            throw std::runtime_error("Edge does not exist");
        }
        int weight = adjacencyList[src][dest];
        if (weight < 0) numOfNegativeEdges--;
        adjacencyList[src][dest] = NO_EDGE;  // Remove edge by setting it to NO_EDGE
        adjacencyList[dest][src] = NO_EDGE;
    }

    // Print the graph
    void Graph::printGraph() const {
        for (int i = 0; i < numVertices; i++) {
            std::cout << "Vertex " << i << ": ";
            for (int j = 0; j < numVertices; j++) {
                if (adjacencyList[i][j] != NO_EDGE) {  // Only print existing edges
                    std::cout << "(" << j << ", " << adjacencyList[i][j] << ") ";
                }
            }
            std::cout << std::endl;
        }
    }

    // Check if there are negative edges
    bool Graph::haveNegativeEdges() const {
        return (numOfNegativeEdges != 0);
    }

    // Getter for number of vertices
    int Graph::getNumVertices() const {
        return numVertices;
    }

    // Getter for adjacency list (const version)
    const int** Graph::getAdjacencyList() const {
        return const_cast<const int**>(adjacencyList);
    }


    // Destructor
    Graph::~Graph() {
        for (int i = 0; i < numVertices; i++) {
            delete[] adjacencyList[i];
        }
        delete[] adjacencyList;
    }

}
