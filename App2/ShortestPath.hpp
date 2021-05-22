#ifndef ShortestPath_hpp
#define ShortestPath_hpp

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"
#include "structures/Additional.hpp"
#include <fstream>

class ShortestPath
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
    void Dijkstry();
    void lDijkstry(int src, int dst);
    void mDijkstry();
    void BellmanFord();
    void lBellmanFord();
    void mBellmanFord();
    
public:
    ShortestPath();
    ~ShortestPath();

    void mainLoop();
};

#endif