#ifndef DisjointedSet_hpp
#define DisjointedSet_hpp

#include "heap.hpp"

struct DNode{
    int up, rank;
};

class DisjointedSet
{
private:
    DNode* w;
public:
    DisjointedSet(int n);
    ~DisjointedSet();
    void makeSet(int v);
    int findSet(int v);
    void unionSets(Edge e);
};

#endif