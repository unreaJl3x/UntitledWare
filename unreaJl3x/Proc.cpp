#include "Proc.h"

DWORD Proc::GetPid(char* pName) {
    PROCESSENTRY32 pEntry;pEntry.dwSize=sizeof(PROCESSENTRY32);
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if (snap == INVALID_HANDLE_VALUE) { cout << "Меня заебал хендл" << endl; return -2; }

    if (Process32First(snap,&pEntry)) {
        //cout << "Exe file " << pEntry.szExeFile << "     |     Process id " << pEntry.th32ProcessID << endl;
        while (Process32Next(snap,&pEntry)) {
            if (!strcmp(pName, pEntry.szExeFile)) { CloseHandle(snap);return pEntry.th32ProcessID; }
        }
    }

    CloseHandle(snap);
    //cout << "Pizdec"<<endl;
    return -1;
}

HANDLE Proc::GetHandle(DWORD pID) { return OpenProcess(PROCESS_ALL_ACCESS,false, pID);}

uintptr_t Proc::GetModuleAddress(DWORD pID, const char* mName) {
    MODULEENTRY32 mEntry; mEntry.dwSize = sizeof(MODULEENTRY32);
    //cout <<"id" << pID << endl;
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,pID);
    if (snap == INVALID_HANDLE_VALUE) { cout << "INVALID HANDLE "; return 0; }

    if (Module32First(snap,&mEntry)) {
        while (Module32Next(snap,&mEntry)) {
            //cout << (char*)mEntry.szModule << endl;
            if (!strcmp(mName, (char*)mEntry.szModule)) {CloseHandle(snap);return (uintptr_t)mEntry.modBaseAddr;}
        }
    }
    CloseHandle(snap);
    return -1;
}

string Proc::GetCurrentProcessName()
{
    PROCESSENTRY32 pEntry;pEntry.dwSize=sizeof(PROCESSENTRY32);
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if (snap == INVALID_HANDLE_VALUE) {return ""; }

    if (Process32First(snap,&pEntry)) {
        while (Process32Next(snap,&pEntry)) {
            if (GetCurrentProcessId() == pEntry.th32ProcessID) { CloseHandle(snap);return pEntry.szExeFile; }
        }
    }

    CloseHandle(snap);
    return "";
}