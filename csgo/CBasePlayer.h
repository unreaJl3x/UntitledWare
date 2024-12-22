#ifndef UNTITLEDWARE_CBASEPLAYER_H
#define UNTITLEDWARE_CBASEPLAYER_H

#include <iostream>
#include <windows.h>
#include <map>
#include <vector>

#include "ProcessManager.h"
#include "csgo_signatures.h"
using namespace std;
#define DUMP hazedumper::netvars

class CBasePlayer {
private:
    ProcessManager* pm;
    Output* out;
    uintptr_t localAddress;

    vector<string> keys;
    template <typename T>
    void addOffset(string, uintptr_t, T);
    class Date {
    public:
        uintptr_t addr;
        BYTE varible;

        Date() = default;
        Date(BYTE var, uintptr_t addr) {
            this->addr = addr;
            this->varible=(BYTE)var;
        }
    };

public:
    map<string, Date> memory;

    bool UpdateDate();

    CBasePlayer() = default;
    CBasePlayer(ProcessManager*, Output*, uintptr_t);
};

#endif //UNTITLEDWARE_CBASEPLAYER_H