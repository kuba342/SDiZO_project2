#ifndef MST_hpp
#define MST_hpp

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"

class MST
{
private:
    MatrixGraph* mGraph;
    ListGraph* lGraph;

    void readFromFile();
    void generateGraph();
    void showGraphs();
    void Prim();
    void Kruskal();

public:
    MST();
    ~MST();

    void mainLoop();
};

#endif