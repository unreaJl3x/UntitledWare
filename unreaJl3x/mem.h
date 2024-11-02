
#ifndef UNTITLEDWARE_MEM_H
#define UNTITLEDWARE_MEM_H
#include <windows.h>

namespace Memory {
    template <typename T>
    T Read(HANDLE h,uintptr_t addr) {
        T value = { };
        ReadProcessMemory(h, (LPVOID)(addr), &value, sizeof(T), NULL);
        return value;
    }
    template <typename T>
    bool Write(HANDLE h,uintptr_t addr, T date) {
        return WriteProcessMemory(h, (LPVOID)(addr), &date, sizeof(T), NULL);;
    }
}

#endif