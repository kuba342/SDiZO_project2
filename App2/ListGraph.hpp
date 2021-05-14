#ifndef ListGraph_hpp
#define ListGraph_hpp

#include "BiList.hpp"

class ListGraph
{
private:
    int V;
    int E;
    BiList **table;

public:
    ListGraph();
    ListGraph(int V, int E);
    ~ListGraph();

    void addEdge();
    void addNode();
    void removeEdge();
    void removeNode();
    //Settery i gettery
    int getV();
    int getE();

};

#endif
