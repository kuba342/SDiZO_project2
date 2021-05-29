#ifndef MST_hpp
#define MST_hpp

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"
#include "structures/Additional.hpp"
#include "structures/DisjointedSet.hpp"
#include "structures/BiList.hpp"
#include <fstream>
#include "structures/Queue.hpp"
#include "clock.hpp"

class MST
{
private:
    MatrixGraph* mGraph;
    ListGraph* lGraph;
    Additional* lib;
    std::string path;
    std::fstream handler;
    Clock* clock;

    //Elementy wyznaczania MST
    Queue* queue;
    ListGraph* lmst;
    MatrixGraph* mmst;
    DisjointedSet* dst;
    bool* visited;

    void readFromFile();
    void readData(std::string name);
    void generateGraph(double d, int n);
    void showGraphs();
    void Prim();
    void lPrim();
    void mPrim();
    void Kruskal();
    void lKruskal();
    void mKruskal();

public:
    MST();
    ~MST();

    void mainLoop();
};

#endif