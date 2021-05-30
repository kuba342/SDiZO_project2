#ifndef heap_hpp
#define heap_hpp

struct Edge
{
    int beg;
    int end;
    int weight;
};

class heap
{
private:
    Edge* array;
    int heapSize;

    //relacja rodzic - syn
    int parent(int i);
    int leftSon(int i);
    int rightSon(int i);

public:
    heap();
    ~heap();
    Edge getRoot();
    void heapPush(Edge edge);
    void heapPop();
};

#endif