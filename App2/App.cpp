#include <iostream>
#include "App.hpp"
#include "clock.hpp"
#include "structures/BiList.hpp"

using namespace std;

App::App(){
    this->cl = new Clock();
    this->wsk = new BiList();
}

App::~App(){
}

int main(void){
    App app = App();
    app.mainLoop();
    return 0;
}

void App::mainLoop(){
    
    this->wsk->addAtTheEnd(1,20);
    this->wsk->addAtTheEnd(2,40);
    this->wsk->addAtTheBeginning(0,0);
    this->wsk->showList();
    this->wsk->showList();
}
