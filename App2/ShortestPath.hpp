#ifndef ShortestPath_hpp
#define ShortestPath_hpp

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"

class ShortestPath
{
private:
    MatrixGraph* mGraph;
    ListGraph* lGraph;

    void readFromFile();
    void generateGraph();
    void showGraphs();
    void Dijkstry();
    void BellmanFord();

public:
    ShortestPath();
    ~ShortestPath();

    void mainLoop();
};

#endif