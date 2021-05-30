#include "MST.hpp"

#include <string>
#include <unistd.h>

MST::MST(){
    this->lGraph = nullptr;
    this->mGraph = nullptr;
    this->lib = new Additional();
    this->path = "D:/STUDIA/IV semestr/SDiZO/Projekt/SDiZO_project2/App2/";
    this->clock = new Clock();
    this->queue = nullptr;
    this->lmst = nullptr;
    this->mmst = nullptr;
    this->dst = nullptr;
    this->visited = nullptr;
}

MST::~MST(){

}

void MST::mainLoop(){
    char decision;
    while(1){
        system("cls");
        std::cout << "Wprowadz znak operacji do wykonania:\n"
                  << "1. Wczytaj dane z pliku.\n"
                  << "2. Wygeneruj graf losowo.\n"
                  << "3. Wyswietl graf listowo i macierzowo na ekranie\n"
                  << "4. Algorytm Prima z wyswietleniem wynikow listowo i macierzowo\n"
                  << "5. Algorytm Kruskala z wyswietleniem wynikow listowo i macierzowo\n"
                  << "X lub x. Zakoncz podprogram\n\n"
                  << "Wprowadz znak operacji: ";
        std::cin >> decision;
        fflush(stdin);

        switch(decision){
            case '1':
                system("cls");
                readFromFile();
                break;
            case '2':
                system("cls");
                generating();
                break;
            case '3':
                system("cls");
                showGraphs();
                break;
            case '4':
                system("cls");
                Prim();
                break;
            case '5':
                system("cls");
                Kruskal();
                break;
            
            case 'X':
                system("cls");
                return;
                break;
            case 'x':
                system("cls");
                return;
                break;
            
            default:
                system("cls");
                std::cout << "Niepoprawny znak operacji!";
                sleep(2);
                break;
        }
    }
}

void MST::readFromFile(){
    system("cls");
    if(this->lGraph == nullptr && this->mGraph == nullptr){
        readData("graf.txt");
    }
    else{
        char decision;
        std::cout << "Czy chcesz nadpisac obecny graf?\n"
                  << "Wpisz T lub N:";
        std::cin >> decision;

        switch(decision){
            case 'T':
                system("cls");
                readData("graf.txt");
                break;
            case 't':
                system("cls");
                readData("graf.txt");
                break;

            case 'N':
                system("cls");
                std::cout << "Operacja anulowana!";
                sleep(2);
                return;
                break;
            case 'n':
                system("cls");
                std::cout << "Operacja anulowana!";
                sleep(2);
                return;
                break;
            default:
                system("cls");
                std::cout << "Operacja anulowana - zly znak!";
                sleep(2);
                return;
                break;
        }
    }
}

void MST::readData(std::string name){
    int e,v,indeks,indeks2,n;
    int beg, end, weight;
    std::string str1, str2, str3;
    this->handler.close();
    std::string Path = this->path + name;
    this->handler.open(Path);

    std::string line;

    //Pobieram pierwszą linię
    getline(this->handler, line);

    if(this->lGraph != nullptr){
        delete this->lGraph;
    }
    if(this->mGraph != nullptr){
        delete this->mGraph;
    }

    indeks = line.find(' ');
    n = line.find('\n');
    //Pierwsza liczba
    str1 = line.substr(0,indeks);
    str2 = line.substr(indeks+1, n-indeks-1);

    if(this->lib->isNum(str1) && this->lib->isNum(str2)){
        e = std::stoi(str1);
        v = std::stoi(str2);
        this->lGraph = new ListGraph(v);
        this->mGraph = new MatrixGraph(v,e);
    }
    else{
        system("cls");
        std::cout << "Blad wczytywania z pliku!";
        sleep(2);
        this->handler.close();
        return;
    }

    //Odczytywanie krawędzi
    for(int i=0; i<e; i++){
        getline(this->handler, line);
        indeks = line.find(' ');
        indeks2 = line.find_last_of(' ');
        n = line.find('\n');
        str1 = line.substr(0,indeks);
        str2 = line.substr(indeks+1, indeks2-indeks-1);
        str3 = line.substr(indeks2+1, n-indeks2-1);
        if(this->lib->isNum(str1)){
            beg = std::stoi(str1);
        }
        else{
            system("cls");
            std::cout << "Nieprawidlowa pierwsza dana krawedzi!";
            sleep(2);
            this->handler.close();
            return;
        }

        if(this->lib->isNum(str2)){
            end = std::stoi(str2);
        }
        else{
            system("cls");
            std::cout << "Nieprawidlowa druga dana krawedzi!";
            sleep(2);
            this->handler.close();
            return;
        }

        if(this->lib->isNum(str3)){
            weight = std::stoi(str3);
        }
        else{
            system("cls");
            std::cout << "Nieprawidlowa druga dana krawedzi!";
            sleep(2);
            this->handler.close();
            return;
        }

        this->lGraph->addEdge(beg, end, weight);
        this->mGraph->addEdge(beg, end, weight);
    }
}

void MST::generating(){
    char decision;
    if(this->lGraph != nullptr || this->mGraph != nullptr){
        system("cls");
        std::cout << "Czy chcesz nadpisac obecny graf?\n"
                  << "Wpisz T lub N: ";
        std::cin >> decision;
        fflush(stdin);

        switch(decision){
            case 't':
                system("cls");
                gendecision();
                break;
            case 'T':
                system("cls");
                gendecision();
                break;

            case 'n':
                return;
                break;
            case 'N':
                return;
                break;
            default:
                system("cls");
                std::cout << "Wprowadzono niepoprawny znak\n"
                          << "Koniec operacji!";
                sleep(2);
                return;
                break;
        }
    }
    else{
        gendecision();
    }
}

void MST::gendecision(){
    int v = 0;
    double d = 0;
    char decision1, decision2;

    do{
        std::cout << "Ile wierzcholkow ma miec graf?\n\n"
                << "1. 20\n"
                << "2. 50\n"
                << "3. 100\n"
                << "4. 150\n"
                << "5. 200\n\n"
                << "Wpisz numer: ";
        std::cin >> decision1;
        fflush(stdin);

        switch(decision1){
            case '1':
                v = 20;
                break;
            case '2':
                v = 50;
                break;
            case '3':
                v = 100;
                break;
            case '4':
                v = 150;
                break;
            case '5':
                v = 200;
                break;
            default:
                system("cls");
                std::cout << "Nieprawidlowy znak!";
                sleep(2);
                break;
        }
    }while(v == 0);
    system("cls");
    do{
        std::cout << "Jaka gestosc grafu?\n\n"
                  << "1. 25%\n"
                  << "2. 50%\n"
                  << "3. 75%\n"
                  << "4. 99%\n\n"
                  << "Wpisz numer: ";
        std::cin >> decision2;
        fflush(stdin);

        switch(decision2){
            case '1':
                d = 0.25;
                break;
            case '2':
                d = 0.5;
                break;
            case '3':
                d = 0.75;
                break;
            case '4':
                d = 0.99;
                break;
            default:
                system("cls");
                std::cout << "Nieprawidlowy znak!";
                sleep(2);
                break;
        }
    }while(d == 0);

    generateGraph(d,v);
}

void MST::generateGraph(double d, int n){
    //Poszukuję takiej liczby krawędzi, aby zgadzała się z gęstością
    int counter = 0;
    double m;
    m = (d*n*n-d*n)/2;
    int edges = (int)m;      //Rzutuję na typ całkowity

    //Zakładam, że generuję grafy dla gęstości większych bądź równych 25%
    //Oraz dla liczby wierzchołków większej niż 10

    //Tworzenie nowego grafu
    this->lGraph = new ListGraph(n);
    this->mGraph = new MatrixGraph(n,edges);

    //generator pseudolosowych
    srand(time(NULL));
    //Tworzę kręgosłup z losowymi wagami
    for(int i=0; i<n-1; i++, counter++){
        int input = rand()%9999;
        this->lGraph->addEdge(i,i+1,input);
        this->mGraph->addEdge(i,i+1,input);
    }

    for(int i=counter; i<edges;i++){
        int beg = rand()%(int)n;
        int end;
        do{
            end = rand()%(int)n;
        }while(beg == end);
        int weight = rand()%9999;
        this->lGraph->addEdge(beg, end, weight);
        this->mGraph->addEdge(beg, end, weight);
    }
}

void MST::showGraphs(){
    if(this->lGraph != nullptr & this->mGraph != nullptr){
        system("cls");
        std::cout << "Reprezentacja listowa:\n";
        this->lGraph->showGraph();
        std::cout << "\nReprezentacja macierzowa:\n";
        this->mGraph->showGraph();
        std::cout << "\n\nWcisnij Enter, aby kontynuowac!";
        std::cin.get();
    }
    else{
        system("cls");
        std::cout << "Nie stworzono grafu!\n"
                  << "Anulowano!";
        sleep(2);
    }
}

void MST::Prim(){
    if(this->lGraph == nullptr || this->mGraph == nullptr){
        system("cls");
        std::cout << "Nie wczytano grafu!";
        sleep(2);
        return;
    }
    lPrim();
    this->lmst->showGraph();
    std::cout << "Wcisnij Enter, aby kontynuowac!";
    std::cin.get();
    fflush(stdin);

    mPrim();
    this->mmst->showGraph();
    std::cout << "Wcisnij Enter, aby kontynuowac!";
    std::cin.get();
    fflush(stdin);
}

void MST::lPrim(){
    freeAll();
    int v;
    //kolejka priorytetowa
    this->queue = new heap();
    //MST listowy
    this->lmst = new ListGraph(this->lGraph->getV());
    //Tablica odwiedzonych
    this->visited = new bool[this->lGraph->getV()];

    //Inicjalizacja tablicy odwiedzonych
    for(int i=0; i<this->lGraph->getV(); i++){
        this->visited[i] = false;
    }

    //Minimalne drzewo rozpinające:
    v = 0;                  //wierzchołek startowy
    this->visited[v] = true;      //Odchaczony jako odwiedzony
    
    Edge e;
    BiList* pointer;
    //Dodaję do MST V-1 krawędzi
    for(int i=1; i<this->lGraph->getV(); i++){
        pointer = this->lGraph->getListFromArray(v);
        //Przeglądam listę dla wierzchołka
        for(listElement* p = pointer->getHead(); p!=pointer->getTail()->next; p=p->next){
            if(!visited[p->key]){
                e.beg = v;
                e.end = p->key;
                e.weight = p->weight;
                queue->heapPush(e);
            }
        }

        do{
            e = queue->getRoot();
            queue->heapPop();
        }while(visited[e.end]);
        lmst->addEdge(e.beg, e.end, e.weight);
        visited[e.end] = true;
        v = e.end;
    }
}

void MST::mPrim(){
    freeAll();
    int v;
    //kolejka priorytetowa
    this->queue = new heap();
    //MST macierzowy
    this->mmst = new MatrixGraph(this->mGraph->getV(),this->mGraph->getV()-1);
    //Tablica odwiedzonych
    this->visited = new bool[this->mGraph->getV()];

    //Inicjalizacja tablicy odwiedzonych
    for(int i=0; i<this->mGraph->getV(); i++){
        visited[i] = false;
    }

    //Minimalne drzewo rozpinające:
    v = 0;                  //wierzchołek startowy
    visited[v] = true;      //Odchaczony jako odwiedzony

    //Dodaję do MST V-1 krawędzi
    for(int i=1; i<this->mGraph->getV(); i++){
        Edge e;
        //Przeglądam tablicę dla wierzchołka
        for(int j=0; j<this->mGraph->getE(); j++){
            //Jeśli początek krawędzi
            if(this->mGraph->getMatrix()[v][j] == 1){
                //Szukam końca krawędzi
                for(int k=0; k<this->mGraph->getV(); k++){
                    //Jeśli różny od v wierzchołek
                    if(this->mGraph->getMatrix()[k][j] && k!=v && !this->visited[k]){
                        e.beg = v;
                        e.end = k;
                        e.weight = this->mGraph->getWeights()[j];
                        queue->heapPush(e);
                    }
                }
            }
        }
        do{
            e = queue->getRoot();
            queue->heapPop();
        }while(visited[e.end]);
        mmst->addEdge(e.beg, e.end, e.weight);
        visited[e.end] = true;
        v = e.end;
    }
}

void MST::Kruskal(){
    if(this->lGraph == nullptr || this->mGraph == nullptr){
        system("cls");
        std::cout << "Nie wczytano grafu!";
        sleep(2);
        return;
    }
    lKruskal();
    lmst->showGraph();
    std::cout << "Wcisnij Enter, aby kontynuowac!";
    std::cin.get();
    fflush(stdin);

    mKruskal();
    mmst->showGraph();
    std::cout << "Wcisnij Enter, aby kontynuowac!";
    std::cin.get();
    fflush(stdin);
}

void MST::lKruskal(){
    freeAll();
    //kolejka priorytetowa
    this->queue = new heap();
    //MST listowy
    this->lmst = new ListGraph(this->lGraph->getV());
    //Zbiory rozłączne
    this->dst = new DisjointedSet(this->lGraph->getV());
    //Krawędź
    Edge e;

    //Zbiór rozłączny dla każdego wierzchołka
    for(int i=0; i<this->lGraph->getV(); i++){
        dst->makeSet(i);
    }

    //Krawędzie do kolejki priorytetowej
    for(int i=0; i<this->lGraph->getV(); i++){
        BiList* list = this->lGraph->getListFromArray(i);
        //Iteruję przez wszystkie elementy listy
        for(listElement* j=list->getHead(); j!=list->getTail()->next; j=j->next){
            if(j->key > i){
                e.beg = i;
                e.end = j->key;
                e.weight = j->weight;
                queue->heapPush(e);
            }
        }
    }

    //pętla wykonuje się V-1 razy
    for(int i=1; i<this->lGraph->getV(); i++){
        do{
            e = queue->getRoot();
            queue->heapPop();
        }while(dst->findSet(e.beg) == dst->findSet(e.end));

        lmst->addEdge(e.beg, e.end, e.weight);
        dst->unionSets(e);
    }
}

void MST::mKruskal(){
    freeAll();
    //kolejka priorytetowa
    this->queue = new heap();
    //MST listowy
    this->mmst = new MatrixGraph(this->mGraph->getV(), this->mGraph->getV()-1);
    //Zbiory rozłączne
    this->dst = new DisjointedSet(this->mGraph->getV());
    //Krawędź
    Edge e;

    //Zbiór rozłączny dla każdego wierzchołka
    for(int i=0; i<this->mGraph->getV(); i++){
        dst->makeSet(i);
    }

    //Do kolejki dodaję wszystkie krawędzie grafu
    for(int i=0; i<this->mGraph->getE(); i++){
        //Sprawddzam po wierzchołkach w poszukiwaniu jedynki
        for(int j=0; j<this->mGraph->getV(); j++){
            //Wierzchołek początkowy
            if(this->mGraph->getMatrix()[j][i] == 1){
                //Zaczynam przeszukiwanie dalej w poszukiwaniu końcowego
                for(int x=j+1; x<this->mGraph->getV(); x++){
                    //Jeśli końcowy ma 1
                    if(this->mGraph->getMatrix()[x][i] == 1){
                        e.beg = j;
                        e.end = x;
                        e.weight = this->mGraph->getWeights()[i];
                        queue->heapPush(e);
                    }
                }
            }
        }
    }

    //Pętla wykonuje się V-1 razy
    for(int i=1; i<this->mGraph->getV(); i++){
        do{
            e = queue->getRoot();
            queue->heapPop();
        }while(dst->findSet(e.beg) == dst->findSet(e.end));

        mmst->addEdge(e.beg, e.end, e.weight);
        dst->unionSets(e);
    }
}


void MST::freeAll(){
    //std::cout << "queue\n";
    if(this->queue != nullptr){
        delete this->queue;
        this->queue = nullptr;
    }
    //std::cout << "lmst\n";
    if(this->lmst != nullptr){
        delete this->lmst;
        this->lmst = nullptr;
    }
    //std::cout << "mmst\n";
    if(this->mmst != nullptr){
        delete this->mmst;
        this->mmst = nullptr;
    }
    //std::cout << "dst\n";
    if(this->dst != nullptr){
        delete this->dst;
        this->dst = nullptr;
    }
    //std::cout << "visited\n";
    if(this->visited != nullptr){
        delete [] this->visited;
        this->visited = nullptr;
    }
    //std::cout << "freeEnd\n";
}
