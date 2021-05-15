#include <iostream>
#include "App.hpp"

using namespace std;

App::App(){
    this->cl = new Clock();
}

App::~App(){
}

int main(void){
    App app = App();
    app.mainLoop();
    return 0;
}

void App::mainLoop(){
    ListGraph* wsk = new ListGraph(5);
    MatrixGraph* wsk1 = new MatrixGraph(5,6);
    wsk->addDirectedEdge(1,2,5);
    wsk1->addDirectedEdge(1,2,5);
    wsk->addEdge(0,1,5);
    wsk1->addEdge(0,1,5);
    wsk->showGraph();
    wsk1->showGraph();
}
