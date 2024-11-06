#include "Proc.h"

HANDLE Proc::OpenHandle() {HANDLE h = OpenProcess(PROCESS_ALL_ACCESS,false, csgo.pID); return (h==INVALID_HANDLE_VALUE) ? ((OUTPUT::print("INVALID HANDLE",2,"GetHandle")) ? (h):h) : (h);}

/*          OLD
DWORD Proc::GetPid() {
    PROCESSENTRY32 pEntry;pEntry.dwSize=sizeof(PROCESSENTRY32);
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if (snap == INVALID_HANDLE_VALUE) { OUTPUT::print("INVALID HANDLE",2,"GetPid"); return -2; }

    if (Process32First(snap,&pEntry)) {
        //cout << "Exe file " << pEntry.szExeFile << "     |     Process id " << pEntry.th32ProcessID << endl;
        while (Process32Next(snap,&pEntry)) {
            if (!strcmp(csgo.nameExe.c_str(), pEntry.szExeFile)) { CloseHandle(snap);return pEntry.th32ProcessID; }
        }
    }

    CloseHandle(snap);
    //cout << "Pizdec"<<endl;
    return -1;
}
string Proc::GetCurrentProcessName()
{
    PROCESSENTRY32 pEntry;pEntry.dwSize=sizeof(PROCESSENTRY32);
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if (snap == INVALID_HANDLE_VALUE) {OUTPUT::print("INVALID HANDLE",2,"GetCurrentProcessName"); return ""; }

    if (Process32First(snap,&pEntry)) {
        while (Process32Next(snap,&pEntry)) {
            if (GetCurrentProcessId() == pEntry.th32ProcessID) { CloseHandle(snap);return pEntry.szExeFile; }
        }
    }

    CloseHandle(snap);
    return "";
}
*/

uintptr_t Proc::GetModuleAddress(const char* mName) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,csgo.pID);
    MODULEENTRY32 mEntry; mEntry.dwSize = sizeof(MODULEENTRY32);


    if (snap == INVALID_HANDLE_VALUE) { OUTPUT::print("INVALID HANDLE",2,"GetModuleAddress"); CloseHandle(snap);return 1; }

    if (Module32First(snap, &mEntry)) {
        do {
            if (!strcmp(mName, mEntry.szModule)) {CloseHandle(snap);return (uintptr_t)mEntry.modBaseAddr;}
        }while (Module32Next(snap, &mEntry)) ;
    }
    CloseHandle(snap);
    return 0;
}

int Proc::GetRunningExempls(char* nameexe, int runs)
{
    PROCESSENTRY32 pEntry;pEntry.dwSize=sizeof(PROCESSENTRY32);
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if (snap==INVALID_HANDLE_VALUE) { OUTPUT::print("INVALID HANDLE",2,"FindProcess");return -1; }
    int appsRuns=0;
    if (Process32First(snap, &pEntry)) {
        while (Process32Next(snap,&pEntry)) {
            if (!strcmp(nameexe, pEntry.szExeFile)) {appsRuns++;}
        }
    }
    CloseHandle(snap);
    return appsRuns;
}


// test
Proc::AppDate Proc::GetAppDate(DWORD)
{
    PROCESSENTRY32 pEntry;pEntry.dwSize=sizeof(PROCESSENTRY32);
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if (snap == INVALID_HANDLE_VALUE) {OUTPUT::print("INVALID HANDLE",2,"GetAppDate(DWORD)"); return *new AppDate(); }

    if (Process32First(snap,&pEntry)) {
        while (Process32Next(snap,&pEntry)) {
            if (GetCurrentProcessId() == pEntry.th32ProcessID) { CloseHandle(snap);return *new Proc::AppDate((DWORD)pEntry.th32ProcessID, pEntry.szExeFile); }
        }
    }

    CloseHandle(snap);
    return *new AppDate();
}
Proc::AppDate Proc::GetAppDate(const char* pName)
{
    PROCESSENTRY32 pEntry;pEntry.dwSize=sizeof(PROCESSENTRY32);
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if (snap == INVALID_HANDLE_VALUE) {OUTPUT::print("INVALID HANDLE",2,"GetAppDate(DWORD)"); return *new AppDate(); }

    if (Process32First(snap,&pEntry)) {
        while (Process32Next(snap,&pEntry)) {
            if (!strcmp(pName, pEntry.szExeFile)) { CloseHandle(snap);return *new Proc::AppDate((DWORD)pEntry.th32ProcessID, pEntry.szExeFile); }
        }
    }

    CloseHandle(snap);
    return *new AppDate();
}