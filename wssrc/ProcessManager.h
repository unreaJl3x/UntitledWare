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
public:
    static bool WriteMemory(uintptr_t, int, int*, HANDLE h);

    static bool WriteMemoryA(uintptr_t, int, char*, HANDLE h);

    static int ReadMemory(uintptr_t, int, HANDLE h);

    static string ReadMemoryA(uintptr_t, int, HANDLE h);

    static DWORD GetPID(string*);
    static HANDLE GetHandle(DWORD);
    static HWND GetWindowHandle(string*,string*);

    static uintptr_t GetModuleAddr(string, DWORD);
    static string GetWindowsUser();
};

#endif
