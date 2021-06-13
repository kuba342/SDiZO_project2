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
    void generateGraph(double d, int n);
    
    void showGraphs();
    void Dijkstry();
    void lDijkstry(int src);
    void mDijkstry(int src);
    void BellmanFord();
    void lBellmanFord(int src);
    void mBellmanFord(int src);
    void showShortest(int src, int dst);

    void generating();
    void gendecision(int variant);
    void testing();
    void tests(double d, int n);
    
public:
    ShortestPath();
    ~ShortestPath();

    void mainLoop();
};

#endif