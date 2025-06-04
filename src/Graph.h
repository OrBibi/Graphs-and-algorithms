//orbibiariel@gmail.com
#ifndef GRAPH_H
#define GRAPH_H

#include <limits.h>  // To use INT_MIN

namespace graph {

    class Graph {
    public:
        // Constructor
        Graph(int numVertices);
        
        // Copy Constructor
        Graph(const Graph& other);  

        // Add and remove edges
        void addEdge(int src, int dest, int weight = 1);
        void removeEdge(int src, int dest);

        // Print the graph
        void printGraph() const;

        // Expose data
        int getNumVertices() const;
        const int** getAdjacencyList() const; 
        bool haveNegativeEdges() const;

        // Destructor
        ~Graph();

        static const int NO_EDGE = INT_MIN; // Representing no edge between vertices

    private:
        int numVertices;       // Number of vertices
        int** adjacencyList;   // Adjacency list (2D array)
        int numOfNegativeEdges; // Counter for negative edges
    };

} // namespace graph

#endif
