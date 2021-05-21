#ifndef MST_hpp
#define MST_hpp

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"
#include "structures/Additional.hpp"
#include "structures/DisjointedSet.hpp"
#include "structures/BiList.hpp"
#include <fstream>

class MST
{
private:
    MatrixGraph* mGraph;
    ListGraph* lGraph;
    Additional* lib;
    std::string path;
    std::fstream handler;

    void readFromFile();
    void readData(std::string name);
    void generateGraph();
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