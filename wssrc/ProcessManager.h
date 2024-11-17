#ifndef UNTITLEDWARE_PROCESSMANAGER
#define UNTITLEDWARE_PROCESSMANAGER

#include <iostream>
#include <windows.h>
#include <Tlhelp32.h>

#include "output.h"
#include "app.h"
using namespace std;

class ProcessManager {
private:
    Output* out;
    App* victim;

public:
    template <typename T, T>
    bool Write(uintptr_t);
    template <typename T>
    T Read(uintptr_t);

    DWORD GetPID();
    HANDLE GetHandle();
    HWND GetWindowHandle();

    ProcessManager(Output*, App*);
    ProcessManager() = default;
};

#endif
