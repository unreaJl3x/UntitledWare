#ifndef UNTITLEDWARE_CBASEPLAYER_H
#define UNTITLEDWARE_CBASEPLAYER_H

#include <iostream>
#include <Windows.h>
#include <map>
#include <vector>

#include "map_and_keys.h"
#include "ProcessManager.h"
#include "csgo/hazedumper.h"
#define DUMP hazedumper::netvars
using namespace std;

class CBasePlayer {
private:
    void addOffset(string, uintptr_t, BYTE);
    uintptr_t addr;
    HANDLE handle;
    template <typename T>
    class Date {
    public:
        uintptr_t addr;
        T varible;

        Date() = default;
        Date(T var, uintptr_t addr) {
            this->addr = addr;
            this->varible = var;
        }
    };


public:
    map_and_keys<string, Date<int>> memory;
    void Load(vector<string>);
    uintptr_t GetAddr();

    CBasePlayer(uintptr_t, HANDLE);
    CBasePlayer() = default;
};

#endif //UNTITLEDWARE_CBASEPLAYER_H