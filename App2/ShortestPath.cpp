#include "ShortestPath.hpp"

#include <iostream>
#include <unistd.h>
#include "structures/BiList.hpp"


ShortestPath::ShortestPath(){
    this->lGraph = nullptr;
    this->mGraph = nullptr;
    this->lib = new Additional();
    this->path = "D:/STUDIA/IV semestr/SDiZO/Projekt/SDiZO_project2/App2/";
    this->clock = new Clock();
}

ShortestPath::~ShortestPath(){

}

void ShortestPath::mainLoop(){
    char decision;
    while(1){
        system("cls");
        std::cout << "Wprowadz znak operacji do wykonania:\n"
                  << "1. Wczytaj dane z pliku.\n"
                  << "2. Wygeneruj graf losowo.\n"
                  << "3. Wyswietl graf listowo i macierzowo na ekranie\n"
                  << "4. Algorytm Dijkstry z wyswietleniem wynikow listowo i macierzowo\n"
                  << "5. Algorytm Bellmana-Forda z wyswietleniem wynikow listowo i macierzowo\n"
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
                generateGraph(0.75,10);
                break;
            case '3':
                system("cls");
                showGraphs();
                break;
            case '4':
                system("cls");
                Dijkstry();
                break;
            case '5':
                system("cls");
                BellmanFord();
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

void ShortestPath::readFromFile(){
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

void ShortestPath::readData(std::string name){
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

        this->lGraph->addDirectedEdge(beg, end, weight);
        this->mGraph->addDirectedEdge(beg, end, weight);
    }
}

void ShortestPath::generateGraph(double d, int n){
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
        this->lGraph->addDirectedEdge(i,i+1,input);
        this->mGraph->addDirectedEdge(i,i+1,input);
    }

    for(int i=counter; i<edges;i++){
        int beg = rand()%(int)n;
        int end;
        do{
            end = rand()%(int)n;
        }while(beg == end);
        int weight = rand()%9999;
        this->lGraph->addDirectedEdge(beg, end, weight);
        this->mGraph->addDirectedEdge(beg, end, weight);
    }
}

void ShortestPath::showGraphs(){
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

void ShortestPath::Dijkstry(){
    std::string source, destination;
    int src, dst;
    if(this->lGraph == nullptr || this->mGraph == nullptr){
        system("cls");
        std::cout << "Nie wczytano grafu!";
        sleep(2);
        return;
    }
    std::cout << "Wprowadz wierzcholek poczatkowy: ";
    std::cin >> source;
    fflush(stdin);
    if(this->lib->isNum(source)){
        src = std::stoi(source);
        if(src < this->lGraph->getV()){
            std::cout << "\nWprowadz wierzcholek docelowy: ";
            std::cin >> destination;
            if(this->lib->isNum(destination)){
                dst = std::stoi(destination);
                if(dst < this->lGraph->getV()){

                    //Tu wywołuję algorytm Dijkstry dla dwóch wierzchołków
                    lDijkstry(src, dst);
                    showShortest(dst);
                    mDijkstry(src, dst);
                    showShortest(dst);
                }
                else{
                    system("cls");
                    std::cout<<"Nie ma takiego wierzcholka!";
                    sleep(2);
                    return;
                }
            }
            else{
                system("cls");
                std::cout << "Wprowadzono zle znaki!";
                sleep(2);
                return;
            }
        }
        else{
            system("cls");
            std::cout<<"Nie ma takiego wierzcholka!";
            sleep(2);
            return;
        }
    }
    else{
        system("cls");
        std::cout << "Wprowadzono zle znaki!";
        sleep(2);
        return;
    }
}

void ShortestPath::showShortest(int dst){
    this->stack = new int[this->lGraph->getV()];
    int wsk = 0;

    std::cout << "Koszty:\n";
    for(int i=0; i<this->lGraph->getV(); i++){
        std::cout << " " << d[i] << " ";
    }
    std::cout << "\n\n";

    std::cout << "Rodzice:\n";
    for(int i=0; i<this->lGraph->getV(); i++){
        std::cout << " " << parent[i] << " ";
    }
    std::cout << "\n";

    //Ścieżka na stosie
    for(int i=dst; i>-1; i=parent[i]){
        stack[wsk++] = i;
    }

    std::cout << "Sciezka: [";
    //Wyświetlenie stosu od tyłu z wagą na końcu
    for(int i=wsk-1; i>=0; i--){
        std::cout << " " << stack[i] << " ";
    }
    std::cout << "]\n";
    std::cout << "Weight = " << d[dst];
    std::cout << "\n\nWcisnij Enter, aby kontynuowac!";
    fflush(stdin);
    std::cin.get();
    fflush(stdin);
}

void ShortestPath::lDijkstry(int src, int dst){
    //Tablice dynamiczne
    this->d = new int[this->lGraph->getV()];     //Koszty dojścia
    this->parent = new int[this->lGraph->getV()];    //Tablica poprzedników
    this->visited = new bool[this->lGraph->getV()]; //Tablica odwiedzonych

    //Inicjalizacja tablic dynamicznych
    for(int i=0; i<this->lGraph->getV(); i++){
        d[i] = MAXINT;
        parent[i] = -1;
        visited[i] = false;
    }

    //Koszt dojścia dla źródłowego wierzchołka - 0
    d[src] = 0;

    //Wyznaczenie ścieżek - dla każdego wierzchołka
    for(int i=0; i<this->lGraph->getV(); i++){
        //Znajduję nieodwiedzony
        int j,k;
        for(j=0; visited[j]; j++);
        for(k=j++; j<this->lGraph->getV(); j++){
            if(!visited[j] && (d[j] < d[k])){
                k = j;
            }
        }
        
        //Odwiedzony
        visited[k] = true;

        BiList* list = this->lGraph->getListFromArray(k);
        for(listElement* i=list->getHead(); i!=list->getTail()->next; i=i->next){
            if(!visited[i->key] && (d[i->key] > d[k] + i->weight)){
                d[i->key] = d[k] + i->weight;
                parent[i->key] = k;
            }
        }
    }
}

void ShortestPath::mDijkstry(int src, int dst){
    //Tablice dynamiczne
    this->d = new int[this->mGraph->getV()];     //Koszty dojścia
    this->parent = new int[this->mGraph->getV()];    //Tablica poprzedników
    this->visited = new bool[this->mGraph->getV()]; //Tablica odwiedzonych

    //Inicjalizacja tablic dynamicznych
    for(int i=0; i<this->mGraph->getV(); i++){
        d[i] = MAXINT;
        parent[i] = -1;
        visited[i] = false;
    }

    //Koszt dojścia dla źródłowego wierzchołka - 0
    d[src] = 0;

    //Wyznaczenie ścieżek - dla każdego wierzchołka
    for(int i=0; i<this->mGraph->getV(); i++){
        //Znajduję nieodwiedzony
        int j,k;
        for(j=0; visited[j]; j++);
        for(k=j++; j<this->mGraph->getV(); j++){
            if(!visited[j] && (d[j] < d[k])){
                k = j;
            }
        }
        
        //Odwiedzony
        visited[k] = true;

        //k - numer wiersza, który w tym przypadku będzie stały
        for(int i=0; i<this->mGraph->getE(); i++){
            //Jeśli początek krawędzi
            if(this->mGraph->getMatrix()[k][i] == 1){
                //Iteruję przez wszystkie wirzchołki w poszukiwaniu -1
                for(int j=0; j<this->mGraph->getV(); j++){
                    //Jeśli znaleziony końcowy wierzchołek
                    if(this->mGraph->getMatrix()[j][i] == -1){
                        //Mając całą krawędź sprawdzam zgodnie z algorytmem
                        if(!visited[j] && (d[j] > d[k] + this->mGraph->getWeights()[i])){
                            d[j] = d[k] + this->mGraph->getWeights()[i];
                            parent[j] = k;
                        }
                    }
                }
            }
        }
    }
}

void ShortestPath::BellmanFord(){
    std::string source, destination;
    int src, dst;
    if(this->lGraph == nullptr || this->mGraph == nullptr){
        system("cls");
        std::cout << "Nie wczytano grafu!";
        sleep(2);
        return;
    }
    std::cout << "Wprowadz wierzcholek poczatkowy: ";
    std::cin >> source;
    fflush(stdin);
    if(this->lib->isNum(source)){
        src = std::stoi(source);
        if(src < this->lGraph->getV()){
            std::cout << "\nWprowadz wierzcholek docelowy: ";
            std::cin >> destination;
            if(this->lib->isNum(destination)){
                dst = std::stoi(destination);
                if(dst < this->lGraph->getV()){

                    //Tu wywołuję algorytm Dijkstry dla dwóch wierzchołków
                    lBellmanFord(src, dst);
                    showShortest(dst);
                    mBellmanFord(src, dst);
                    showShortest(dst);
                }
                else{
                    system("cls");
                    std::cout<<"Nie ma takiego wierzcholka!";
                    sleep(2);
                    return;
                }
            }
            else{
                system("cls");
                std::cout << "Wprowadzono zle znaki!";
                sleep(2);
                return;
            }
        }
        else{
            system("cls");
            std::cout<<"Nie ma takiego wierzcholka!";
            sleep(2);
            return;
        }
    }
    else{
        system("cls");
        std::cout << "Wprowadzono zle znaki!";
        sleep(2);
        return;
    }
}

void ShortestPath::lBellmanFord(int src, int dst){
    //Tablice dynamiczne
    this->d = new int[this->lGraph->getV()];     //Koszty dojścia
    this->parent = new int[this->lGraph->getV()];    //Tablica poprzedników
    bool bf, t;

    //Inicjalizacja struktur
    for(int i=0; i<this->lGraph->getV(); i++){
        d[i] = MAXINT;
        parent[i] = -1;
    }

    //Zeruję koszt wierzchołka startowego
    d[src] = 0;

    //Pętla relaksacji
    for(int i=1; i<this->lGraph->getV(); i++){
        t = true;
        //Przejście przez kolejne wierzchołki
        for(int j=0; j<this->lGraph->getV(); j++){
            BiList* list;
            list = this->lGraph->getListFromArray(j);
            //Przeglądanie sąsiadów wierzchołka
            for(listElement* i=list->getHead(); i!=list->getTail()->next; i=i->next){
                //Warunek relaksacji
                if(d[j] != MAXINT && d[i->key] > d[j] + i->weight){
                    t = false;
                    d[i->key] = d[j] + i->weight;
                    parent[i->key] = j;
                }
            }
        }
        if(t){
            break;
        }
    }
    //Pomijam sprawdzenie ujemnego cyklu, ponieważ w założeniach wagi są dodatnie
}

void ShortestPath::mBellmanFord(int src, int dst){
    //Tablice dynamiczne
    this->d = new int[this->lGraph->getV()];     //Koszty dojścia
    this->parent = new int[this->lGraph->getV()];    //Tablica poprzedników
    bool bf,t;

    //Inicjalizacja struktur
    for(int i=0; i<this->lGraph->getV(); i++){
        d[i] = MAXINT;
        parent[i] = -1;
    }

    //Zeruję koszt wierzchołka startowego
    d[src] = 0;

    //Pętla relaksacji - V-1 razy wykonana
    for(int i=1; i<this->mGraph->getV(); i++){
        t = true;
        //Przejście przez kolejne wierzchołki
        for(int j=0; j<this->mGraph->getV(); j++){
            //Poszukuję początek krawędzi
            for(int k=0; k<this->mGraph->getE(); k++){
                if(this->mGraph->getMatrix()[j][k] == 1){
                    //teraz poszukuję koniec krawędzi
                    for(int l=0; l<this->mGraph->getV(); l++){
                        if(this->mGraph->getMatrix()[l][k] == -1){
                            //W tym momencie indeks k jest kolumną (wagi)
                            //indeks j jest wierzchołkiem początkowym
                            //indeks l jest wierzchołkiem końcowym
                            if(d[j] != MAXINT && d[l] > d[j] + this->mGraph->getWeights()[k]){
                                t = false;
                                d[l] = d[j] + this->mGraph->getWeights()[k];
                                parent[l] = j;
                            }
                        }
                    }
                }
            }
        }
        if(t){
            bf = true;
            break;
        }
    }
}