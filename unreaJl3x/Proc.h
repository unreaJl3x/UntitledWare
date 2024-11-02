#pragma once

#include <windows.h>
#include <TlHelp32.h>
#include <iostream>

using namespace std;

namespace Proc {
    DWORD GetPid(char*);
    HANDLE GetHandle(DWORD);
    uintptr_t GetModuleAddress(DWORD,const char*);
    string GetCurrentProcessName();
}