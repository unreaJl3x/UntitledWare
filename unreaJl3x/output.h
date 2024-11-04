#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <windows.h>
using namespace std;

namespace OUTPUT {
    #define CNAME "UntitledWare"
    #define PREFIX "UW:"
    #define STATUS_OK 1
    #define STATUS_BAD 2
    #define STATUS_NULL 0

    bool print(string, int, string);
    void print_msg(string);
}



#endif
