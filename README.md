# Graph Assignment
orbibiariel@gmail.com

## Description
This project implements an undirected graph using an adjacency list. Several graph algorithms such as BFS, DFS, Dijkstra, Prim, and Kruskal are implemented to perform various operations on the graph. The project also includes helper classes to manage dynamic data structures used by the graph algorithms.

## Directory Structure
GRAPH-ASSIGNMENT/
│
├── src/                           # Source files for graph-related classes and algorithms
│   ├── Algorithms.cpp             # Implementation of graph algorithms (BFS, DFS, Dijkstra, Prim and Kruskal)
│   ├── Graph.cpp                  # Implementation of the Graph class
│   ├── Queue.cpp                  # Implementation of the Queue class
│   ├── Vector.cpp                 # Implementation of the Vector class
│   ├── UnionFind.cpp              # Implementation of the UnionFind class
│   └── main.cpp                   # Main program entry point
│
├── tests/                         # Unit tests for graph and algorithms
│   ├── test_graph.cpp             # Unit tests for graph-related functionalities
│   └── doctest.h                  # Doctest header for running tests
│
├── Makefile                       # Makefile to compile and build the project
└── README.md                      # This file


## Classes

### 1. **Graph**: 
The `Graph` class handles the graph structure and its edges. It uses an adjacency list to represent the graph, where each node points to a list of its neighboring nodes and the corresponding edge weights. The class provides methods for adding edges, retrieving adjacency lists, and other utilities necessary for manipulating the graph.

Key Features:
- Stores the graph as an adjacency list.
- Can add edges with weights.
- Provides access to adjacency lists for graph traversal.
- Allows the graph to be traversed with various algorithms like BFS, DFS, Dijkstra, Prim, and Kruskal.

Important to know:
- Adding a new edge between 2 vertices that already have an edge will replace the old edge with the new one
- A vertex edge cannot be added to itself (from v to v)

### 2. **Algorithms**:
The `Algorithms` class implements various algorithms for graph traversal and pathfinding, which can be applied to any instance of the `Graph` class. These algorithms include:
- **BFS (Breadth-First Search)**: A graph traversal algorithm that explores all vertices at the present depth level before moving on to vertices at the next depth level (Finds the shortest path without considering the weight of the edges).
- **DFS (Depth-First Search)**: A graph traversal algorithm that explores as far down a branch as possible before backtracking.
- if you dont input v it will chosse randomly!!!
- **Dijkstra's Algorithm**: A shortest-path algorithm that finds the minimum distance from a source node to all other nodes in a weighted graph.
- **Prim's Algorithm**: A minimum spanning tree (MST) algorithm that builds an MST by repeatedly adding the smallest edge that connects a vertex in the MST to a vertex outside the MST.
- if you dont input v it will chosse randomly!!!
- **Kruskal's Algorithm**: Another MST algorithm that sorts all edges by weight and adds them to the MST if they do not form a cycle.

### 3. **Queue**:
The `Queue` class is a simple implementation of a queue data structure, used by the BFS algorithm to store vertices that need to be visited next. A queue follows a FIFO (First-In-First-Out) order, which is essential for BFS's level-order traversal.

Key Features:
- Implements a basic queue for storing and retrieving elements.
- Provides enqueue and dequeue operations for adding and removing items.
- Used in BFS to manage the order in which vertices are explored.

### 4. **Vector**:
The `Vector` class is a dynamic array implementation that provides an efficient way to store and access data. It is used in multiple places within the graph and algorithms to store lists of neighbors, edge weights, or distances. The `Vector` class dynamically resizes as needed to accommodate more elements.

Key Features:
- A dynamic array that can grow or shrink in size as elements are added or removed.
- Provides direct access to elements by index.
- Used extensively in the `Graph` class to manage adjacency lists.

### 5. **UnionFind**:
The `UnionFind` class is used to manage disjoint sets of elements, which is especially useful in Kruskal's algorithm for detecting cycles when adding edges to the MST. The class supports two main operations:
- **Find**: Determines the root of the set containing a particular element.
- **Union**: Merges two sets together if they are disjoint.

Key Features:
- Implements the union-find (disjoint-set) data structure.
- Supports path compression to optimize find operations.
- Used in Kruskal’s algorithm to efficiently check and manage connected components.

## How to Run

To build and run the project, you can use the provided `Makefile` to manage the compilation and execution:

- **To run the main program**:  
  Run `make Main`. This will compile and execute the main program, which typically includes graph construction, algorithm execution, and printing results.

- **To run unit tests**:  
  Run `make test`. This will compile and execute the tests for the algorithms and graph operations, ensuring that the implementation behaves as expected.

- **To check for memory leaks**:  
  Run `make valgrind`. This will execute the unit tests under **Valgrind**, a tool that helps detect memory leaks and memory management issues.


