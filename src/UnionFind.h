//orbibiariel@gmail.com
#ifndef UNIONFIND_H
#define UNIONFIND_H

class UnionFind {
public:
    // Constructor
    UnionFind(int size);

    // Find the root of the set containing element i
    int find(int i);

    // Union (merge) the sets containing elements x and y
    void unionSets(int x, int y);

    // Destructor
    ~UnionFind();

private:
    int* parent;  // Pointer to array storing the parent of each element
    int* rank;    // Pointer to array storing the rank (or depth) of each tree
};

#endif
