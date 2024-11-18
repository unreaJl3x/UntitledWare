#ifndef UNTITLEDWARE_APP_H
#define UNTITLEDWARE_APP_H

#include <iostream>
#include <windows.h>

#include "output.h"
using namespace std;

class App {
private:
    Output* out;
public:
    string nameApp;
    string nameExe;
    string IpClassNameWindow;

    DWORD pId;
    HANDLE pHandle;
    HWND hwnd;

    void SetHeader(string);
    App(string,string,string, Output*);
    App() = default;
};


#endif
