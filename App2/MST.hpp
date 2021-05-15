#ifndef MST_hpp
#define MST_hpp

#include "MatrixGraph.hpp"
#include "ListGraph.hpp"

class MST
{
private:
    MatrixGraph* mGraph;
    ListGraph* lGraph;

public:
    MST();
    ~MST();

    void mainLoop();
};

#endif