#ifndef App_hpp
#define App_hpp

#include "structures/BiList.hpp"
#include "clock.hpp"

using namespace std;

class App
{
private:
    BiList* wsk;
    Clock* cl;
public:
    App();
    ~App();
    void mainLoop();
};

#endif
