#include "heap.hpp"

heap::heap(/* args */){
    this->heapSize = 0;
    this->array = new Edge[heapSize];
}

heap::~heap(){
    delete this->array;
}

/**************METODY OBLICZAJĄCE INDEKSY******/
int heap::parent(int i){
    return (i-1)/2;
}

int heap::leftSon(int i){
    return (2*1)+1;
}

int heap::rightSon(int i){
    return (2*i)+2;
}

void heap::heapPush(Edge e){
    if(this->heapSize == 0){
        this->heapSize++;
        this->array = new Edge[heapSize];
        this->array[0] = e;
    }
    else{
        int child = this->heapSize;
        this->heapSize++;
        int parent = this->parent(child);

        //Alokacja pamięci
        Edge* Tab;
        Tab = new Edge[heapSize];
        for(int i=0; i<child; i++){
            Tab[i] = this->array[i];
        }
        delete [] array;
        this->array = Tab;

        while(child>0 && this->array[parent].weight > e.weight){
            this->array[child] = this->array[parent];
            child = parent;
            parent = this->parent(child);
        }
        this->array[child] = e;
    }
}

void heap::heapPop(){
    if(this->heapSize){
        int i,j;
        Edge v;
        this->heapSize--;

        v = this->array[heapSize];
        i = 0;
        j = 1;

        while(j<heapSize){
            if((j+1 < heapSize) && (this->array[j+1].weight < this->array[j].weight)){
                j++;
            }
            if(v.weight <= this->array[j].weight){
                break;
            }
            this->array[i] = this->array[j];
            i = j;
            j = (2*j)+1;
        }
        this->array[i] = v;

        //Nowa lokalizacja
        Edge* Tab;
        Tab = new Edge[heapSize];
        for(int i=0; i<heapSize; i++){
            Tab[i] = this->array[i];
        }
        delete [] array;
        this->array = Tab;
    }
    else{
        return;
    }
}

Edge heap::getRoot(){
    return this->array[0];
}