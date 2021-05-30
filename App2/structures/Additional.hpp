#ifndef Additional_hpp
#define Additional_hpp

#include <string>

class Additional{
public:
    Additional();
    ~Additional();
    bool isNum(std::string str);
    int average(int* Tab, int size);
    long average(long* Tab, int size);
};

#endif