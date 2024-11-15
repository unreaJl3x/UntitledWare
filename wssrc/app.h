#ifndef UNTITLEDWARE_APP_H
#define UNTITLEDWARE_APP_H

#include <iostream>
#include <windows.h>

#include "output.h"
#include "FileSystemManager.h"
#include "ProcessManager.h"
using namespace std;

class App {
private:
Output* out;

public:
    string nameApp;
    string version;
    bool lisensed;

DWORD pId;
HANDLE pHandle;
HWND hwnd;
    void SetHeader();
    App(string, string, bool, Output*);
};


#endif //UNTITLEDWARE_APP_H
