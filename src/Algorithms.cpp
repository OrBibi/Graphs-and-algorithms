//orbibiariel@gmail.com
#include "Algorithms.h"
#include "Queue.h"
#include "Vector.h"
#include "Graph.h"
#include "UnionFind.h"
#include <climits>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <iostream>

namespace graph {

    // 1. BFS
    Graph Algorithms::bfs(const Graph& graph, int start) {
        int numVertices = graph.getNumVertices();

        // The vector to save the distance
        Vector distances(numVertices);
        for (int i = 0; i < numVertices; i++) {
            distances.push_back(-1);  // all distance start from -1
        }

        // Arr the checks if this is the first visit
        bool* visited = new bool[numVertices] {false};

        // queue for the vertices
        Queue queue(numVertices);

        // start from the v start
        visited[start] = true;
        distances.set(start, 0);  // distance to himself is 0
        queue.enqueue(start);  //add him to the queue

        // adding the neighbors in a loop
        while (!queue.isEmpty()) {
            int vertex = queue.dequeue();

            // check all the vertices
            for (int i = 0; i < numVertices; i++) {
                // if they are neighbors and the weight is not NO_EDGE, add it to the queue
                if (graph.getAdjacencyList()[vertex][i] != Graph::NO_EDGE && !visited[i]) {
                    visited[i] = true;
                    distances.set(i, distances.get(vertex) + 1); // set the distance
                    queue.enqueue(i); // add vertices i to the queue
                }
            }
        }
        // from vector to graph
        Graph bfsGraph(numVertices);
        for (int i = 0; i < numVertices; i++) {
            int temp =distances.get(i);
            if(temp!=-1 && i != start){
                bfsGraph.addEdge(start,i,temp);
            }
        }
        delete[] visited;  // release memory

        return bfsGraph;  // return the distances bfs graph
    }

    // DFS
    // DFS Helper Function that builds the DFS tree (graph)
    void dfsHelper(const Graph& graph, int vertex, bool* visited, Graph& dfsGraph) {
        visited[vertex] = true; // Mark the current vertex as visited

        // Iterate over all the neighbors of the current vertex
        for (int i = 0; i < graph.getNumVertices(); i++) {
            // If there is an edge and the neighbor has not been visited
            if (graph.getAdjacencyList()[vertex][i] != Graph::NO_EDGE && !visited[i]) {
                dfsGraph.addEdge(vertex, i); // Add an edge to the DFS graph
                dfsHelper(graph, i, visited, dfsGraph); // Recursively visit the neighbor
            }
        }
    }

    // DFS function that returns a DFS graph
    Graph Algorithms::dfs(const Graph& graph, int randomStart) {
        int numVertices = graph.getNumVertices();
        
        // Create a vector to keep track of the visited vertices
        bool* visited = new bool[numVertices] {false}; // Array to track visited vertices
        Graph dfsGraph(numVertices); // Create a new graph to store the DFS tree

        // If no good input or no input - initialize random start vertex
        if (randomStart < 0 || randomStart >= numVertices) {
            if(randomStart == -1){
                srand(time(0)); // Initialize the random seed based on current time
                randomStart = rand() % numVertices; // Choose a random starting vertex
            }
            else{
                throw std::runtime_error("The vertex you chosse is not it the graph!");
            }
            
        }

        // Perform DFS starting from the random vertex
        dfsHelper(graph, randomStart, visited, dfsGraph);

        // Now we need to make sure all vertices are visited, even if they belong to a different component
        for (int i = 0; i < numVertices; i++) {
            // If this vertex hasn't been visited, perform DFS on it as a new start point
            if (!visited[i]) {
                dfsHelper(graph, i, visited, dfsGraph);
            }
        }

        delete[] visited; // Free the dynamically allocated memory for the visited array
        return dfsGraph; // Return the DFS graph that contains the DFS tree
    }

    // Dijkstra
    Graph Algorithms::dijkstra(const Graph& graph, int start) {
        // check for negative edges
        if (graph.haveNegativeEdges()) {
            throw std::runtime_error("Graph contains negative edges, Dijkstra's algorithm cannot be used.");
        }
        int numVertices = graph.getNumVertices();
        // check the vertices
        if(start<0 || start>=numVertices){
            throw std::runtime_error("The vertex you chosse is not it the graph!");
        }
        // Initialize all nodes as unvisited
        bool* visited = new bool[numVertices] {false};  

        // Create a result vector to store the shortest distances
        Vector result;
        for (int i = 0; i < numVertices; i++) {
            result.push_back(INT_MAX);  // Set all distances to infinity initially
        }
        result.set(start, 0);  // Distance from start to itself is 0

        // Main loop of Dijkstra's algorithm
        while (true) {
            int minDist = INT_MAX;  // Start with a large number
            int u = -1;  // Variable to store the node with the minimum distance

            // Find the unvisited vertex with the smallest distance
            for (int i = 0; i < numVertices; i++) {
                if (!visited[i] && result.get(i) < minDist) {
                    minDist = result.get(i);  // Update minDist
                    u = i;  // Update the vertex u
                }
            }

            // If no unvisited node was found (i.e., all remaining nodes are unreachable)
            if (u == -1) {
                break;  // All remaining nodes are disconnected, exit the loop
            }

            visited[u] = true;  // Mark the current node as visited

            // Update the distances of the adjacent vertices
            for (int v = 0; v < numVertices; v++) {
                // If there is an edge and the adjacent vertex hasn't been visited yet
                if (graph.getAdjacencyList()[u][v] != Graph::NO_EDGE && !visited[v] &&
                    result.get(u) + graph.getAdjacencyList()[u][v] < result.get(v)) {
                    result.set(v, result.get(u) + graph.getAdjacencyList()[u][v]);  // Relax the edge
                }
            }
        }
        // from vector to graph
        Graph dijkstraGraph(numVertices);
        for (int i = 0; i < numVertices; i++) {
            int temp = result.get(i);
            if(temp!=-1 && i != start){
                dijkstraGraph.addEdge(start,i,temp);
            }
        }
        
        // Free the dynamically allocated memory
        delete[] visited;
        
        return dijkstraGraph;  // Return the graph containing shortest distances
    }

    // Prim
    Graph Algorithms::prim(const Graph& graph, int start /*=-1*/) {
        // check for negative edges
        if (graph.haveNegativeEdges()) {
            throw std::runtime_error("Graph contains negative edges, Prim's algorithm cannot be used.");
        }
        int numVertices = graph.getNumVertices();

        // If no good input or no input - initialize random start vertex
        if (start < 0 || start >= numVertices) {
            if (start==-1){
                std::cout << "No input, choose random start vertex!" << std::endl;
                srand(time(0)); 
                start = rand() % numVertices;
            }
            else{
                throw std::runtime_error("The vertex you chosse is not it the graph!");
            }
              
        }

        // initialize visited, key and parent
        bool* visited = new bool[numVertices] {false};
        int* key = new int[numVertices];
        int* parent = new int[numVertices];

        for (int i = 0; i < numVertices; i++) {
            key[i] = INT_MAX;
            parent[i] = -1;
        }
        key[start] = 0;

        // main loop to add n-1 edges
        for (int count = 0; count < numVertices ; count++) {
            int minKey = INT_MAX;
            int u = -1;

            // Step 1: Find the vertex with the minimum weight that is not yet visited
            for (int v = 0; v < numVertices; v++) {
                if (!visited[v] && key[v] < minKey) {
                    minKey = key[v];
                    u = v;
                }
            }

            // If no vertex was found, this means the graph is disconnected
            if (u == -1) {
            // Release memory
            delete[] visited;
            delete[] key;
            delete[] parent;
                throw std::runtime_error("Graph is disconnected, no MST can be formed.");
            }

            // Mark the selected vertex as visited
            visited[u] = true;

            // Step 2: Update the key and parent for the neighboring vertices
            for (int v = 0; v < numVertices; v++) {
                int weight = graph.getAdjacencyList()[u][v];
                // Make sure the edge exists
                if (weight != Graph::NO_EDGE && !visited[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                }
            }
        }

        // Create the MST graph by adding the edges
        Graph mstGraph(numVertices);
        for (int i = 0; i < numVertices; i++) {
            if (parent[i] != -1) {
                mstGraph.addEdge(parent[i], i, graph.getAdjacencyList()[parent[i]][i]);
            }
        }

        // Release memory
        delete[] visited;
        delete[] key;
        delete[] parent;

        return mstGraph;  // return the MST
    }

    // Kruskal
    Graph Algorithms::kruskal(const Graph& graph) {
        int numVertices = graph.getNumVertices();

        // initialize 3 vectors to use as the edges
        Vector srcVertices;  // src
        Vector destVertices;  // dest
        Vector weights; 

        // lists of all the edges
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                int weight = graph.getAdjacencyList()[i][j];
                if (weight != Graph::NO_EDGE) {
                    srcVertices.push_back(i);
                    destVertices.push_back(j);
                    weights.push_back(weight);
                }
            }
        }

        // If there are less than numVertices - 1 edges, the graph is disconnected
        if ((weights.getSize()/2) < numVertices - 1) {
            throw std::runtime_error("Graph is disconnected, no MST can be formed.");
        }

        // sort the edges
        int edgeCount = weights.getSize();
        for (int i = 0; i < edgeCount - 1; i++) {
            for (int j = i + 1; j < edgeCount; j++) {
                if (weights.get(i) > weights.get(j)) {
                    // switch weight
                    int tempWeight = weights.get(i);
                    weights.set(i, weights.get(j));
                    weights.set(j, tempWeight);

                    // switch src
                    int tempSrc = srcVertices.get(i);
                    srcVertices.set(i, srcVertices.get(j));
                    srcVertices.set(j, tempSrc);

                    // switch dest
                    int tempDest = destVertices.get(i);
                    destVertices.set(i, destVertices.get(j));
                    destVertices.set(j, tempDest);
                }
            }
        }

        // every vertex is a root
        UnionFind uf(numVertices);

        // graph to return
        Graph mstGraph(numVertices);
        int mstsize = 1;

        // adding the edges that their vertices are in different sets
        for (int i = 0; i < edgeCount; i++) {
            int src = srcVertices.get(i);
            int dest = destVertices.get(i);
            int weight = weights.get(i);

            // if the vertices are in different trees
            if (uf.find(src) != uf.find(dest)) {
                mstGraph.addEdge(src, dest, weight);
                uf.unionSets(src, dest);  // unite them
                mstsize++;
            }
            if (mstsize == numVertices) break;
        }

        // If we did not connect all vertices, throw exception
        if (mstsize != numVertices) {
            throw std::runtime_error("Graph is disconnected, no MST can be formed.");
        }

        return mstGraph;  // return the graph
    }


}
