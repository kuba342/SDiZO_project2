#include "ListGraph.hpp"

ListGraph::ListGraph(int V, int E){
    this->V = V;
    this->E = E;
    this->table = new BiList *[V];
    for(int i=0; i<V; i++){
        this->table[i] = new BiList();
    }
}

ListGraph::~ListGraph(){
    
}

bool ListGraph::addEdge(int beg, int end, int weight){
    if((beg > this->V) || (beg < 0) || (end > this->V) || (end < 0) || (weight < 0)){
        return false;
    }
    else{
        this->table[beg]->addAtTheEnd(end, weight);
        this->table[end]->addAtTheEnd(beg, weight);
    }
    return true;
}

bool ListGraph::addDirectedEdge(int beg, int end, int weight){
    if((beg > this->V) || (beg < 0) || (end > this->V) || (end < 0) || (weight < 0)){
        return false;
    }
    else{
        this->table[beg]->addAtTheEnd(end, weight);
    }
    return true;
}

void ListGraph::showGraph(){
    for(int i=0; i<this->V; i++){
        std::cout << "Node " << i << " ";
        this->table[i]->showList();
        std::cout << "\n";
    }
}