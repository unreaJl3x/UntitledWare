#include "ProcessManager.h"

int ProcessManager::ReadMemory(uintptr_t offset, int sizeMemory, HANDLE h) {
    int value;
    bool result = ReadProcessMemory(h, LPVOID(offset), &value, sizeMemory, NULL);
    if (!result) { Output::print("Cannot read memory in point . " + (offset), result, "ProcessManager.Read"); }
    return value;
}

string ProcessManager::ReadMemoryA(uintptr_t offset, int sizeMemory, HANDLE h) {
    string value;
    bool result = ReadProcessMemory(h, LPVOID(offset), &value, sizeMemory, NULL);
    if (!result) { Output::print("Cannot read memory in point . " + (offset), result, "ProcessManager.Read"); }
    return value;
}

bool ProcessManager::WriteMemory(uintptr_t addr, int sizeMemory, int *value, HANDLE h) {
    bool result = WriteProcessMemory(h, LPVOID(addr), value, sizeMemory, NULL);
    if (!result) { Output::print("Cannot write to the point . " + addr, result, "ProcessManager.Write"); }
    return result;
}

bool ProcessManager::WriteMemoryA(uintptr_t addr, int sizeMemory, char *value, HANDLE h) {
    bool result = WriteProcessMemory(h, LPVOID(addr), value, sizeMemory, NULL);
    if (!result) { Output::print("Cannot write to the point . " + addr, result, "ProcessManager.Write"); }
    return result;
}

DWORD ProcessManager::GetPID(string *nameExe) {
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) {
        Output::print("INVALID HANDLE SNAP", false, "ProcessManager.GetPID");
        return -1;
    }

    if (Process32First(snap, &pEntry)) {
        do {
            if (pEntry.szExeFile == *nameExe) {
                CloseHandle(snap);
                return pEntry.th32ProcessID;
            }
        } while (Process32Next(snap, &pEntry));
    }

    CloseHandle(snap);
    return -1;
}

HANDLE ProcessManager::GetHandle(DWORD pID) {
    return OpenProcess(PROCESS_ALL_ACCESS, true, pID);
}

HWND ProcessManager::GetWindowHandle(string* IpClassNameWindow, string* nameApp) {
    return FindWindow(IpClassNameWindow->c_str(), nameApp->c_str());
}

uintptr_t ProcessManager::GetModuleAddr(string mName, DWORD id) {
    MODULEENTRY32 mEntry;
    mEntry.dwSize = sizeof(MODULEENTRY32);
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, id);
    if (snap == INVALID_HANDLE_VALUE) {
        Output::print("INVALID HANDLE SNAP", false, "");
        CloseHandle(snap);
        return -2;
    }

    if (Module32First(snap, &mEntry)) {
        do {
            if (mEntry.szModule == mName) {
                CloseHandle(snap);
                return (uintptr_t) mEntry.modBaseAddr;
            }
        } while (Module32Next(snap, &mEntry));
    }
    CloseHandle(snap);
    return -1;
}

string ProcessManager::GetWindowsUser() {
    TCHAR username[UNLEN + 1];
    DWORD size = UNLEN + 1;
    GetUserName((TCHAR *) username, &size);
    string user = username;
    return "user";
}

