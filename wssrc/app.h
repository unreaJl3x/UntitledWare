#ifndef UNTITLEDWARE_APP_H
#define UNTITLEDWARE_APP_H

#include <iostream>
#include <windows.h>

#include "ProcessManager.h"
#include "output.h"
using namespace std;

class App {
public:
    string nameApp;
    string nameExe;
    string IpClassNameWindow;

    DWORD pId;
    HANDLE pHandle;
    HWND hwnd;

    bool running;

    bool isRunning();

    void SetHeader(string);
    App(string, string, string);
};


#endif
