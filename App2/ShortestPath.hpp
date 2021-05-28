#ifndef ShortestPath_hpp
#define ShortestPath_hpp

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"
#include "structures/Additional.hpp"
#include <fstream>
#include "clock.hpp"

class ShortestPath
{
private:
    MatrixGraph* mGraph;
    ListGraph* lGraph;
    Additional* lib;
    std::string path;
    std::fstream handler;
    Clock* clock;

    //Elementy wyznaczania ścieżek
    int MAXINT = 2147483647;
    int* d;
    int* parent;
    bool* visited;
    int* stack;

    void readFromFile();
    void readData(std::string name);
    void generateGraph();
    void showGraphs();
    void Dijkstry();
    void lDijkstry(int src, int dst);
    void mDijkstry(int src, int dst);
    void BellmanFord();
    void lBellmanFord(int src, int dst);
    void mBellmanFord(int src, int dst);
    void showShortest(int dst);
    
public:
    ShortestPath();
    ~ShortestPath();

    void mainLoop();
};

#endif