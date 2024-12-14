#include "ProcessManager.h"

#include <Lmcons.h>
#include <utility>

ProcessManager::ProcessManager(Output* out, App newApp){
    this->out = out;
    this->app = newApp;
}

template<typename T>
T ProcessManager::Read(uintptr_t offset) {
    T value = {};
    bool result = ReadProcessMemory(app.pHandle, (offset), &value, sizeof(T), NULL);
    if(!result) { out->print("Cannot read memory in point . "+(offset),result,"ProcessManager.Read"); }
    return value;
}

template<typename T, T value>
bool ProcessManager::Write(uintptr_t addr) {
    bool result = WriteProcessMemory(app.pHandle, addr, value, sizeof(T), NULL);
    if (!result) { out->print("Cannot write to the point . "+addr,result,"ProcessManager.Write"); }
    return result;
}

DWORD ProcessManager::GetPID() {
    PROCESSENTRY32 pEntry; pEntry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap==INVALID_HANDLE_VALUE) { out->print("INVALID HANDLE SNAP",false,"ProcessManager.GetPID"); return -1;}

    if (Process32First(snap, &pEntry)) {
        do {
            if ( pEntry.szExeFile==app.nameExe ) { CloseHandle(snap); return pEntry.th32ProcessID; }
        } while(Process32Next(snap, &pEntry));
    }

    CloseHandle(snap);
    return -1;
}

HANDLE ProcessManager::GetHandle() {return OpenProcess(PROCESS_ALL_ACCESS, true, app.pId); }

HWND ProcessManager::GetWindowHandle() {
    return FindWindow(app.IpClassNameWindow.c_str(), app.nameApp.c_str());//012DD6F0
}

uintptr_t ProcessManager::GetModuleAddr(string mName) {
    MODULEENTRY32 mEntry; mEntry.dwSize = sizeof(MODULEENTRY32);
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, app.pId);
    if ( snap==INVALID_HANDLE_VALUE ) { out->print("INVALID HANDLE SNAP",false,""); CloseHandle(snap); return -2; }

    if (Module32First(snap, &mEntry)) {
        do {
            cout << mEntry.szModule <<endl;
            if ( mEntry.szModule == mName ) { CloseHandle(snap); return (uintptr_t)mEntry.modBaseAddr; }
        } while (Module32Next(snap, &mEntry));
    }
    CloseHandle(snap);
    return -1;
}

string ProcessManager::GetWindowsUser() {
    TCHAR username[UNLEN + 1];
    DWORD size = UNLEN + 1;
    GetUserName((TCHAR*)username, &size);
    string user = username;
    return user;
}