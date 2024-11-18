#ifndef UNTITLEDWARE_OUTPUT_H
#define UNTITLEDWARE_OUTPUT_H

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
    void input();
    Output() = default;
};


#endif //UNTITLEDWARE_OUTPUT_H
