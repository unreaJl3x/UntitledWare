#pragma once

#include <windows.h>
#include <TlHelp32.h>
#include <iostream>

#include "globals.h"
#include "output.h"
//using namespace std;

namespace Proc {
    string GetWinUser();
    HANDLE OpenHandle();
    uintptr_t GetModuleAddress(const char*);

    bool GetRunningExempls(char*);

    //test
    class AppDate {
    public:
        char* name{};
        DWORD id = -1;
        AppDate(DWORD id, char* name) {this->id = id; this->name = name;}
        AppDate() = default;
    };

    AppDate GetAppDate(const char*);
    AppDate GetAppDate(DWORD);
}