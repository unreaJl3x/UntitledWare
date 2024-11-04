#pragma once

#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>

#include "globals.h"
#include "output.h"
using namespace std;

namespace Proc {
    DWORD GetPid();
    HANDLE GetHandle();
    uintptr_t GetModuleAddress(const char*);
    string GetCurrentProcessName();
    int FindProcess(string);
}