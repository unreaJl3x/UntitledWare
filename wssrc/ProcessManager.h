#ifndef UNTITLEDWARE_PROCESSMANAGER_H
#define UNTITLEDWARE_PROCESSMANAGER_H

#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <vector>

class ProcessManager {
public:
    static bool WriteMemory(uintptr_t, int, int*, HANDLE h);
    static bool WriteMemoryA(uintptr_t, int, char*, HANDLE h);

    static int ReadMemory(uintptr_t, int, HANDLE h);
    static std::string ReadMemoryA(uintptr_t, int, HANDLE h);

    static DWORD GetPID(std::string*);
    static HANDLE GetHandle(DWORD);
    static HWND GetWindowHandle(std::string*,std::string*);

    static uintptr_t GetModuleAddr(std::string, DWORD);
    static std::string GetWindowsUser();
    static std::vector<PROCESSENTRY32> GetAllProcessEntry(std::string*);
};

#endif