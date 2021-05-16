#include "Queue.hpp"

Queue::Queue(int pos){
    this->heap = new Edge[pos];
    this->position = 0;
}

Queue::~Queue(){
    delete [] heap;
}

Edge Queue::front(){
    return this->heap[0];
}

int Queue::parent(int x){
    return (x-1)/2;
}

int Queue::leftSon(int x){
    return (2*x) + 1;
}

void Queue::push(Edge edge){
    int i, j;
    this->position++;
    i = this->position;
    j = parent(i);

    while(i && this->heap[j].weight > edge.weight){
        this->heap[i] = this->heap[j];
        i=j;
        j = parent(i);
    }

    this->heap[i] = edge;
}

void Queue::pop(){
    int i, j;
    Edge edge;

    if(this->position){
        edge = this->heap[--this->position];
        i = 0;
        j = 1;

        while(j<this->position){
            if((j+1 < this->position) && (this->heap[j+1].weight < this->heap[j].weight)){
                j++;
            }
            if(edge.weight <= this->heap[j].weight){
                break;
            }
            this->heap[i] = this->heap[j];
            i = j;
            j = leftSon(j);
        }

        this->heap[i] = edge;
    }
}
