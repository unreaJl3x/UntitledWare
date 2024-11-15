#ifndef UNTITLEDWARE_OUTPUT
#define UNTITLEDWARE_OUTPUT

#include <iostream>
using namespace std;

#define BAD "FF"
#define OK "OK"

class Output {
private:
    const string litteral = "|*> ";
    const string prefix ="UW";

public:
    void print(string, int, string);
    void printMSG();
};


#endif
