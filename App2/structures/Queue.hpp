#ifndef Queue_hpp
#define Queue_hpp

struct Edge
{
    int beg;
    int end;
    int weight;
};

class Queue
{
private:
    Edge* heap;
    int position;
    int parent(int x);
    int leftSon(int x);
public:
    Queue(int pos);
    ~Queue();
    Edge front();
    void push(Edge edge);
    void pop();
};

#endif