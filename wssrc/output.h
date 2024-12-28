#ifndef UNTITLEDWARE_OUTPUT_H
#define UNTITLEDWARE_OUTPUT_H

#include <iostream>
using namespace std;

#define BAD "FF"
#define OK "OK"

class Output {
private:
    static inline const string litteral = "|*> ";
    static inline const string prefix ="UW";

public:
    static void print(string, int, string);
    static void printMSG();
    Output() = default;
};


#endif //UNTITLEDWARE_OUTPUT_H
