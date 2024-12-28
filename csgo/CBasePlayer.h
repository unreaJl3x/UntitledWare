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
    uintptr_t localAddress;
    void addOffset(string, uintptr_t, BYTE);

    class Date {
    public:
        uintptr_t addr;
        BYTE varible;

        Date() = default;
        Date(BYTE var, uintptr_t addr) {
            this->addr = addr;
            this->varible = var;
        }
    };


public:
    vector<string> keys;
    map<string, Date> memory;

    CBasePlayer() = default;
    CBasePlayer(uintptr_t);
};

#endif //UNTITLEDWARE_CBASEPLAYER_H