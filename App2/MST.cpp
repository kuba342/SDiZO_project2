#include "MST.hpp"

#include <string>
#include <unistd.h>
#include "structures/Queue.hpp"

MST::MST(){
    this->lGraph = nullptr;
    this->mGraph = nullptr;
    this->lib = new Additional();
    this->path = "D:/STUDIA/IV semestr/SDiZO/Projekt/SDiZO_project2/App2/";
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
                generateGraph();
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

void MST::generateGraph(){

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
    lPrim();
    mPrim();
}

void MST::lPrim(){
    if(this->lGraph == nullptr){
        system("cls");
        std::cout << "Nie wczytano grafu!";
        sleep(2);
        return;
    }

    int v;
    //kolejka priorytetowa
    Queue* queue = new Queue(this->lGraph->getE());
    //MST listowy
    ListGraph* mst = new ListGraph(this->lGraph->getV());
    //Tablica odwiedzonych
    bool* visited = new bool [this->lGraph->getV()];

    //Inicjalizacja tablicy odwiedzonych
    for(int i=0; i<this->lGraph->getV(); i++){
        visited[i] = false;
    }

    //Minimalne drzewo rozpinające:
    v = 0;                  //wierzchołek startowy
    visited[v] = true;      //Odchaczony jako odwiedzony
    
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
                queue->push(e);
            }
        }

        do{
            e = queue->front();
            queue->pop();
        }while(visited[e.end]);
        mst->addEdge(e.beg, e.end, e.weight);
        visited[e.end] = true;
        v = e.end;
    }

    mst->showGraph();
    std::cout << "Wcisnij Enter, aby kontynuowac!";
    std::cin.get();
    fflush(stdin);
}

void MST::mPrim(){
    if(this->mGraph == nullptr){
        system("cls");
        std::cout << "Nie wczytano grafu!";
        sleep(2);
        return;
    }
    
    int v, w;
    //kolejka priorytetowa
    Queue* queue = new Queue(this->mGraph->getE());
    //MST macierzowy
    MatrixGraph* mst = new MatrixGraph(this->mGraph->getV(),this->mGraph->getV()-1);
    //Tablica odwiedzonych
    bool* visited = new bool [this->mGraph->getV()];

    //Inicjalizacja tablicy odwiedzonych
    for(int i=0; i<this->mGraph->getV(); i++){
        visited[i] = false;
    }

    //Minimalne drzewo rozpinające:
    v = 0;                  //wierzchołek startowy
    visited[v] = true;      //Odchaczony jako odwiedzony
    
    Edge e;

    //Dodaję do MST V-1 krawędzi
    for(int i=1; i<this->mGraph->getV(); i++){
        //Przeglądam tablicę dla wierzchołka
        for(int j=0; j<this->mGraph->getE(); j++){
            //Jeśli początek krawędzi
            if(this->mGraph->getMatrix()[v][j] == 1){
                //Szukam końca krawędzi
                for(int k=0; k<this->mGraph->getV(); k++){
                    if(this->mGraph->getMatrix()[k][j] && k!=v){
                        w = k;  //wierzchołek końcowy
                        break;
                    }
                }

                e.beg = v;
                e.end = w;
                e.weight = this->mGraph->getWeights()[j];
                queue->push(e);
            }
        }

        do{
            e = queue->front();
            queue->pop();
        }while(visited[e.end]);
        mst->addEdge(e.beg, e.end, e.weight);
        visited[e.end] = true;
        v = e.end;
    }

    mst->showGraph();
    std::cout << "Wcisnij Enter, aby kontynuowac!";
    std::cin.get();
    fflush(stdin);
}

void MST::Kruskal(){
    lKruskal();
    //mKruskal();
}

void MST::lKruskal(){
    if(this->lGraph == nullptr){
        system("cls");
        std::cout << "Nie wczytano grafu!";
        sleep(2);
        return;
    }

    //kolejka priorytetowa
    Queue* queue = new Queue(this->mGraph->getE());
    //MST listowy
    ListGraph* mst = new ListGraph(this->lGraph->getV());
    //Zbiory rozłączne
    DisjointedSet* dst = new DisjointedSet(this->lGraph->getV());
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
                queue->push(e);
            }
        }
    }

    //pętla wykonuje się V-1 razy
    for(int i=1; i<this->lGraph->getV(); i++){
        do{
            e = queue->front();
            queue->pop();
        }while(dst->findSet(e.beg) == dst->findSet(e.end));

        mst->addEdge(e.beg, e.end, e.weight);
        dst->unionSets(e);
    }

    mst->showGraph();
    std::cout << "Wcisnij Enter, aby kontynuowac!";
    std::cin.get();
    fflush(stdin);
}

void MST::mKruskal(){

}

