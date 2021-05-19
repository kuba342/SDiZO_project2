#ifndef ListGraph_hpp
#define ListGraph_hpp

#include "structures/BiList.hpp"
#include <string>

/**
 * Reprezentacja jako lista następników
 */
class ListGraph
{
private:
    int V;
    int E;
    BiList **table;

public:
    ListGraph();
    ListGraph(int V);
    ~ListGraph();

    bool addEdge(int beg, int end, int weight);
    bool addDirectedEdge(int beg, int end, int weight);

    //Settery i gettery
    BiList* getListFromArray(int indeks);
    int getV();
    int getE();

    //reprezentacja
    void showGraph();
};

#endif
