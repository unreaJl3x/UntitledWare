#ifndef UNTITLEDWARE_PROCESSMANAGER_H
#define UNTITLEDWARE_PROCESSMANAGER_H

#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <Lmcons.h>
#include <utility>

#include "app.h"
#include "output.h"
using namespace std;

class ProcessManager {
private:
    Output* out;

public:
    App app;

    template <int, int*>
    bool WriteMemory(uintptr_t);

    template <int, char*>
    bool WriteMemory(uintptr_t);

    template <int>
    int ReadMemory(uintptr_t);

    template <int>
    string ReadMemoryA(uintptr_t);

    DWORD GetPID();
    HANDLE GetHandle();
    HWND GetWindowHandle();
    bool SetWindowTitle(string);
    uintptr_t GetModuleAddr(string);
    static string GetWindowsUser();

    ProcessManager(Output *, App);
};

#endif
