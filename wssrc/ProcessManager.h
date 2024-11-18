#ifndef UNTITLEDWARE_PROCESSMANAGER_H
#define UNTITLEDWARE_PROCESSMANAGER_H

#include <iostream>
#include <windows.h>
#include <TlHelp32.h>

#include "app.h"
#include "output.h"
using namespace std;

class ProcessManager {
private:
    Output* out;
public:
    App app;
    template <typename T, T>
    bool Write(uintptr_t);

    template <typename T>
    T Read(uintptr_t);

    DWORD GetPID();
    HANDLE GetHandle();
    HWND GetWindowHandle();
    uintptr_t GetModuleAddr(string);

    ProcessManager(Output *, App);
};

#endif
