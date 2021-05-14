#include "ListGraph.hpp"
#include "BiList.hpp"

ListGraph::ListGraph(int V, int E){
    this->V = V;
    this->E = E;
    this->table = new BiList *[this->V];
}

ListGraph::~ListGraph(){
    
}