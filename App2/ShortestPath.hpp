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
    void BellmanFord();
    
public:
    ShortestPath();
    ~ShortestPath();

    void mainLoop();
};

#endif