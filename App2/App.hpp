#ifndef App_hpp
#define App_hpp

#include "clock.hpp"
#include "ListGraph.hpp"
#include "MatrixGraph.hpp"

using namespace std;

class App
{
private:
    Clock* cl;
public:
    App();
    ~App();
    void mainLoop();
};

#endif
