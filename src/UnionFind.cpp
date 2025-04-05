//orbibiariel@gmail.com
#include "UnionFind.h"

// Constructor
UnionFind::UnionFind(int size) {
    parent = new int[size];  // Array to store the parent of each element
    rank = new int[size];    // Array to store the rank (or depth) of each tree
    for (int i = 0; i < size; i++) {
        parent[i] = i;       // Initially, each element is its own parent (each element is its own set)
        rank[i] = 0;         // Initially, all ranks are set to 0
    }
}

// Find the root of the set containing element i, with path compression
int UnionFind::find(int i) {
    if (parent[i] != i) {
        parent[i] = find(parent[i]);  // Recursively find the root, applying path compression
    }
    return parent[i];
}

// Union (merge) the sets containing elements x and y
void UnionFind::unionSets(int x, int y) {
    int rootX = find(x);  // Find the root of the set containing x
    int rootY = find(y);  // Find the root of the set containing y

    if (rootX != rootY) {  // Only union if they are in different sets
        // Union by rank: attach the smaller tree to the root of the larger tree
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;  // RootX becomes the parent of RootY
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;  // RootY becomes the parent of RootX
        } else {
            parent[rootY] = rootX;  // If ranks are equal, choose one root as the parent
            rank[rootX]++;          // Increase the rank of the new root
        }
    }
}

// Destructor
UnionFind::~UnionFind() {
    delete[] parent;  
    delete[] rank;   
}
