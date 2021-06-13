#ifndef MST_hpp
#define MST_hpp

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"
#include "structures/Additional.hpp"
#include "structures/DisjointedSet.hpp"
#include "structures/BiList.hpp"
#include <fstream>
#include "clock.hpp"
#include "structures/heap.hpp"

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
    //Queue* queue;
    heap* queue;
    ListGraph* lmst;
    MatrixGraph* mmst;
    DisjointedSet* dst;
    bool* visited;

    void readFromFile();
    void readData(std::string name);
    void generating();
    void gendecision(int variant);
    void generateGraph(double d, int n);
    void showGraphs();
    void Prim();
    void lPrim(int src);
    void mPrim(int src);
    void Kruskal();
    void lKruskal();
    void mKruskal();
    void freeAll();

    void testing();
    void tests(double d, int n);

public:
    MST();
    ~MST();

    void mainLoop();
};

#endif