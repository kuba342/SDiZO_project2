#ifndef App_hpp
#define App_hpp

#include "clock.hpp"
#include "MST.hpp"
#include "ShortestPath.hpp"

using namespace std;

class App
{
private:
    MST* mst;
    ShortestPath* path;
    Clock* cl;
public:
    App();
    ~App();
    void mainLoop();
    void MSToperations();
    void shortestPathOperations();
};

#endif
