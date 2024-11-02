#include <iostream>
#include <windows.h>

#include "unreaJl3x/Proc.h"
#include "hack.h"
using namespace std;

// На дорабртку
struct pDate {
	string appName = "Counter Strike: Global Offensive";
	string exeName = "csgo.exe";
	DWORD pID = -1;
	HANDLE handle
	 = INVALID_HANDLE_VALUE;
    bool isSuccessful = false;

    void check() { isSuccessful = pID >= 0 && pID <= 900000 && handle != INVALID_HANDLE_VALUE; }
};

// На дорабртку
bool checkLocalDoubling() {
    int count=0;

    const string pName = Proc::GetCurrentProcessName();
    PROCESSENTRY32 pEntry;pEntry.dwSize=sizeof(PROCESSENTRY32);
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if (snap == INVALID_HANDLE_VALUE) {return false; }

    if (Process32First(snap,&pEntry)) {
        while (Process32Next(snap,&pEntry)) {
            if (!strcmp((char*)pName.c_str(), pEntry.szExeFile)) {count++;}
        }
    }

    CloseHandle(snap);
    return count >= 2;
}

int main() {
    if (checkLocalDoubling()) { ShowWindow(GetConsoleWindow(),SW_HIDE);MessageBox(NULL, "Program alredy running!", "UntitledWare",MB_OK); return 0; }

    pDate date;
    date.pID = Proc::GetPid((char*)date.exeName.c_str());
    date.handle = Proc::GetHandle(date.pID);
    date.check();
    cout << "UW (main.cpp): Process '"<< date.appName << "' have pID is " << date.pID << endl<<endl;
    if (date.isSuccessful) {
        hack(date.handle,date.pID);
    }
    cout << "EXIT......" << endl;

	getchar();
	return 1;
}
