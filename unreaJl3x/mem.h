#ifndef UNTITLEDWARE_MEM_H
#define UNTITLEDWARE_MEM_H
#include <windows.h>
#include "globals.h"

namespace Memory {
    template <typename T>
    T Read(uintptr_t addr) {
        T value = { };
        ReadProcessMemory(csgo.pHandle, (LPVOID)(addr), &value, sizeof(T), NULL);
        return value;
    }
    template <typename T>
    bool Write(uintptr_t addr, T date) {
        return WriteProcessMemory(csgo.pHandle, (LPVOID)(addr), &date, sizeof(T), NULL);;
    }
}

#endif