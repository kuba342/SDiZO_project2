#include "DisjointedSet.hpp"

DisjointedSet::DisjointedSet(int n){
    this->w = new DNode[n];
}

DisjointedSet::~DisjointedSet(){
    delete [] w;
}

void DisjointedSet::makeSet(int v){
    this->w[v].up = v;
    this->w[v].rank = 0;
}

int DisjointedSet::findSet(int v){
    if(this->w[v].up != v){
        this->w[v].up = findSet(this->w[v].up);
    }
    return this->w[v].up;
}

void DisjointedSet::unionSets(Edge e){
    int u, v;

    u = findSet(e.beg);
    v = findSet(e.end);

    if(u != v){
        if(this->w[u].rank > this->w[v].rank){
            this->w[v].up = u;
        }
        else{
            this->w[u].up = v;
            if(this->w[u].rank == this->w[v].rank){
                this->w[v].rank++;
            }
        }
    }
}
