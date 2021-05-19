#ifndef MatrixGraph_hpp
#define MatrixGraph_hpp

/**
 * Reprezentacja jako macierz incydencji
 */
class MatrixGraph
{
private:
    int V;
    int E;
    int ECount;
    int** matrix;
    int* weights;

public:
    MatrixGraph();
    MatrixGraph(int V, int E);
    ~MatrixGraph();

    bool addEdge(int beg, int end, int weight);
    bool addDirectedEdge(int beg, int end, int weight);

    //Settery i gettery
    int** getMatrix();
    int* getWeights();
    int getV();
    int getE();
    int getECount();

    //reprezentacja
    void showGraph();
};

#endif
