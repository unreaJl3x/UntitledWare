#ifndef UNTITLEDWARE_APP
#define UNTITLEDWARE_APP

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
    string version;
string nameExe;

DWORD pId;
HANDLE pHandle;
HWND hwnd;

    void SetHeader();
    App(string, string, string, string, Output*);
};


#endif
