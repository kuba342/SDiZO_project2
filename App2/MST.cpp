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
                  << "A lub a. Testy automatyczne\n"
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
            case 'a':
                system("cls");
                testing();
                break;
            case 'A':
                system("cls");
                testing();
                break;
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

    //Pobieram pierwsz?? lini??
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

    //Odczytywanie kraw??dzi
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
                gendecision(1);
                break;
            case 'T':
                system("cls");
                gendecision(1);
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
        gendecision(1);
    }
}

void MST::gendecision(int variant){
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

    switch(variant){
        case 1:
            generateGraph(d,v);
            break;
        case 2:
            tests(d,v);
            break;
    }
}

void MST::generateGraph(double d, int n){
    //Poszukuj?? takiej liczby kraw??dzi, aby zgadza??a si?? z g??sto??ci??
    int counter = 0;
    double m;
    m = (d*n*n-d*n)/2;
    int edges = (int)m;      //Rzutuj?? na typ ca??kowity

    //Zak??adam, ??e generuj?? grafy dla g??sto??ci wi??kszych b??d?? r??wnych 25%
    //Oraz dla liczby wierzcho??k??w wi??kszej ni?? 10

    //Tworzenie nowego grafu
    this->lGraph = new ListGraph(n);
    this->mGraph = new MatrixGraph(n,edges);

    //generator pseudolosowych
    srand(time(NULL));
    //Tworz?? kr??gos??up z losowymi wagami
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
    std::string bufor;
    int src;
    if(this->lGraph == nullptr || this->mGraph == nullptr){
        system("cls");
        std::cout << "Nie wczytano grafu!";
        sleep(2);
        return;
    }
    std::cout << "Podaj wierzcholek poczatkowy: ";
    std::cin >> bufor;
    fflush(stdin);
    if(this->lib->isNum(bufor)){
        src = std::stoi(bufor);
        if(src < this->lGraph->getV()){
            lPrim(src);
            std::cout << "Wynik w postaci listowej:\n";
            this->lmst->showGraph();
            std::cout << "\nSuma wag: " << this->lmst->getSumWeights();
            std::cout << "\nWcisnij Enter, aby kontynuowac!";
            std::cin.get();
            fflush(stdin);

            mPrim(src);
            std::cout << "\nWynik w postaci macierzowej:\n";
            this->mmst->showGraph();
            std::cout << "\nSuma wag: " << this->mmst->getSumWeights();
            std::cout << "\nWcisnij Enter, aby kontynuowac!";
            std::cin.get();
            fflush(stdin);
        }
        else{
            system("cls");
            std::cout << "Nie ma takiego wierzcholka!";
            sleep(3);
        }
    }
}

void MST::lPrim(int src){
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

    //Minimalne drzewo rozpinaj??ce:
    v = src;                  //wierzcho??ek startowy
    this->visited[v] = true;      //Odchaczony jako odwiedzony
    
    Edge e;
    BiList* pointer;
    //Dodaj?? do MST V-1 kraw??dzi
    for(int i=1; i<this->lGraph->getV(); i++){
        pointer = this->lGraph->getListFromArray(v);
        //Przegl??dam list?? dla wierzcho??ka
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

void MST::mPrim(int src){
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

    //Minimalne drzewo rozpinaj??ce:
    v = src;                  //wierzcho??ek startowy
    visited[v] = true;      //Odchaczony jako odwiedzony

    //Dodaj?? do MST V-1 kraw??dzi
    for(int i=1; i<this->mGraph->getV(); i++){
        Edge e;
        //Przegl??dam tablic?? dla wierzcho??ka
        for(int j=0; j<this->mGraph->getE(); j++){
            //Je??li pocz??tek kraw??dzi
            if(this->mGraph->getMatrix()[v][j] == 1){
                //Szukam ko??ca kraw??dzi
                for(int k=0; k<this->mGraph->getV(); k++){
                    //Je??li r????ny od v wierzcho??ek
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
    std::cout << "Wynik w postaci listowej:\n";
    this->lmst->showGraph();
    std::cout << "\nSuma wag: " << this->lmst->getSumWeights();
    std::cout << "\nWcisnij Enter, aby kontynuowac!";
    std::cin.get();
    fflush(stdin);

    mKruskal();
    std::cout << "\nWynik w postaci macierzowej:\n";
    this->mmst->showGraph();
    std::cout << "\nSuma wag: " << this->mmst->getSumWeights();
    std::cout << "\nWcisnij Enter, aby kontynuowac!";
    std::cin.get();
    fflush(stdin);
}

void MST::lKruskal(){
    freeAll();
    //kolejka priorytetowa
    this->queue = new heap();
    //MST listowy
    this->lmst = new ListGraph(this->lGraph->getV());
    //Zbiory roz????czne
    this->dst = new DisjointedSet(this->lGraph->getV());
    //Kraw??d??
    Edge e;

    //Zbi??r roz????czny dla ka??dego wierzcho??ka
    for(int i=0; i<this->lGraph->getV(); i++){
        dst->makeSet(i);
    }

    //Kraw??dzie do kolejki priorytetowej
    for(int i=0; i<this->lGraph->getV(); i++){
        BiList* list = this->lGraph->getListFromArray(i);
        //Iteruj?? przez wszystkie elementy listy
        for(listElement* j=list->getHead(); j!=list->getTail()->next; j=j->next){
            if(j->key > i){
                e.beg = i;
                e.end = j->key;
                e.weight = j->weight;
                queue->heapPush(e);
            }
        }
    }

    //p??tla wykonuje si?? V-1 razy
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
    //Zbiory roz????czne
    this->dst = new DisjointedSet(this->mGraph->getV());
    //Kraw??d??
    Edge e;

    //Zbi??r roz????czny dla ka??dego wierzcho??ka
    for(int i=0; i<this->mGraph->getV(); i++){
        dst->makeSet(i);
    }

    //Do kolejki dodaj?? wszystkie kraw??dzie grafu
    for(int i=0; i<this->mGraph->getE(); i++){
        //Sprawddzam po wierzcho??kach w poszukiwaniu jedynki
        for(int j=0; j<this->mGraph->getV(); j++){
            //Wierzcho??ek pocz??tkowy
            if(this->mGraph->getMatrix()[j][i] == 1){
                //Zaczynam przeszukiwanie dalej w poszukiwaniu ko??cowego
                for(int x=j+1; x<this->mGraph->getV(); x++){
                    //Je??li ko??cowy ma 1
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

    //P??tla wykonuje si?? V-1 razy
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

void MST::testing(){
    gendecision(2);
}

void MST::tests(double d, int n){
    //Liczba pr??b
    int count = 50;
    //Tabela na rezultaty
    long long Tab[count];
    char decision;
    do{
        system("cls");
        std::cout << "Ktory algorytm przeanalizowac?\n\n"
                << "1. Prim listowy\n"
                << "2. Prim macierzowy\n"
                << "3. Kruskal listowy\n"
                << "4. Kruskal macierzowy\n"
                << "Wpisz numer: ";
        std::cin >> decision;
        fflush(stdin);
    }while(decision != '1' && decision != '2' && decision != '3' && decision != '4');

    for(int i=0; i<count; i++){
        Tab[i] = 0;
    }

    system("cls");
    std::cout << "Process: ";

    for(int i=0; i<count; i++){
        do{
            generateGraph(d,n);
            switch(decision){
                case '1':
                    this->clock->startTime();
                    lPrim(0);
                    this->clock->endTime();
                    Tab[i] = this->clock->executionTime();
                    break;
                case '2':
                    this->clock->startTime();
                    mPrim(0);
                    this->clock->endTime();
                    Tab[i] = this->clock->executionTime();
                    break;
                case '3':
                    this->clock->startTime();
                    lKruskal();
                    this->clock->endTime();
                    Tab[i] = this->clock->executionTime();
                    break;
                case '4':
                    this->clock->startTime();
                    mKruskal();
                    this->clock->endTime();
                    Tab[i] = this->clock->executionTime();
                    break;
            }
        }while(Tab[i] == 0);
        std::cout << "!";
    }

    system("cls");
    std::cout << "Tablica rezultatow:\n"
              << "Tab = [";
    for(int i=0; i<count; i++){
        std::cout << " " << Tab[i] << " ";
    }
    std::cout << "]\n\n";
    std::cout << "Srednia: "
              << this->lib->average(Tab,count)
              << "\n\n";
    std::cout << "Wcisnij Enter, aby kontynuowac!";
    std::cin.get();
    fflush(stdin);
}
