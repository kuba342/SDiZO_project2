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
    std::cout << "cos";
    ListGraph* wsk = new ListGraph(4,5);
    std::cout << "cos";
    bool result = wsk->addDirectedEdge(-1,2,5);
    //bool result = wsk->addEdge(0,1,5);
    std::cout << result;
    std::cout << "cos\n";
    wsk->showGraph();

}
