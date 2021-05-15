#include <iostream>
#include <unistd.h>
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
    /*ListGraph* wsk = new ListGraph(5);
    MatrixGraph* wsk1 = new MatrixGraph(5,6);
    wsk->addDirectedEdge(1,2,5);
    wsk1->addDirectedEdge(1,2,5);
    wsk->addEdge(0,1,5);
    wsk1->addEdge(0,1,5);
    wsk->showGraph();
    wsk1->showGraph();*/

    char option;
    while(1){
        system("cls");
        std::cout << "Ktory problem ma byc przeanalizowany?\n"
                << "1. Minimalne drzewo rozpinajace MST.\n"
                << "2. Najkrotsze sciezki\n"
                << "X lub x. Koniec programu\n\n"
                << "Wpisz znak operacji: ";
        std::cin >> option;
        fflush(stdin);

        switch(option){
            case '1':
                system("cls");
                MSToperations();
                break;
            case '2':
                system("cls");
                shortestPathOperations();
                break;

            case 'X':
                system("cls");
                exit(0);
                break;

            case 'x':
                system("cls");
                exit(0);
                break;
            default:
                system("cls");
                std::cout << "Wprowadzono niepoprawny znak!";
                sleep(2);
                break;
        }
    }
}

void App::MSToperations(){
    this->mst = new MST();
    this->mst->mainLoop();
}

void App::shortestPathOperations(){
    this->path = new ShortestPath();
    this->path->mainLoop();
}
