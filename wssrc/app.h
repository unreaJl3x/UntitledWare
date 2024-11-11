#ifndef UNTITLEDWARE_APP_H
#define UNTITLEDWARE_APP_H

#include <iostream>
#include <windows.h>

#include "output.h"
using namespace std;

class App {
public:
    const Output out;
    static string nameApp;
    static string version;
    static bool lisensed;

    void SetHeader();
    App();
};


#endif //UNTITLEDWARE_APP_H
