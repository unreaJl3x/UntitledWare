#include "ProcessManager.h"

ProcessManager::ProcessManager(Output* out, App* newApp) {
    this->out = out;
    this->victim = newApp;
}

template<typename T>
T ProcessManager::Read(uintptr_t addr) {
    T value = {};
    bool result = ReadProcessMemory(victim->pHandle, addr, &value, sizeof(T), NULL);
    if(!result) { out->print("Cannot read memory in point -> "+addr,result,"ProcessManager.Read"); }
    return value;
}

template<typename T, T value>
bool ProcessManager::Write(uintptr_t addr) {
    bool result = WriteProcessMemory(victim->pHandle, addr, value, sizeof(T), NULL);
    if (!result) { out->print("Cannot write to the point -> "+addr,result,"ProcessManager.Write"); }
    return result;
}

DWORD ProcessManager::GetPID() {
    PROCESSENTRY32 pEntry; pEntry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap==INVALID_HANDLE_VALUE) { out->print("INVALID HANDLE SNAP",false,"ProcessManager.GetPID"); }

    if (Process32First(snap, &pEntry)) {
        do {
            if ( pEntry.szExeFile==victim->nameExe ) { CloseHandle(snap); return pEntry.th32ProcessID; }
        } while(Process32Next(snap, &pEntry));
    }
}

HANDLE ProcessManager::GetHandle() {return OpenProcess(PROCESS_ALL_ACCESS, true, victim->pId); }

HWND ProcessManager::GetWindowHandle() {
    return FindWindow("Valve001", victim->nameApp.c_str());
}