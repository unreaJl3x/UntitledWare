#ifndef UNTITLEDWARE_CBASEPLAYER_H
#define UNTITLEDWARE_CBASEPLAYER_H

#include <iostream>
#include <Windows.h>
#include <map>
#include <vector>

#include "ProcessManager.h"
#include "csgo/hazedumper.h"
#define DUMP hazedumper::netvars
using namespace std;

class CBasePlayer {
private:
    void addOffset(string, uintptr_t, BYTE);

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
    vector<string> keys;
    map<string, Date<int> > memory;

    CBasePlayer();
};

#endif //UNTITLEDWARE_CBASEPLAYER_H