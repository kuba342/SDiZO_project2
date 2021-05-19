#ifndef MST_hpp
#define MST_hpp

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"
#include "structures/Additional.hpp"
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
    void Kruskal();

public:
    MST();
    ~MST();

    void mainLoop();
};

#endif