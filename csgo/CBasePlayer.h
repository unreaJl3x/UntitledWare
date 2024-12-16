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
    uintptr_t addr;

    vector<string> keys;
    map<string, uintptr_t> addrsMemory;
    void addOffset(string, uintptr_t);

public:
    int   iHealth;
    int   iArmore;
    int   flags;
    bool  isScoped;
    bool  isReload;
    bool  hasDefuser;
    bool  hasHelmet;
    bool  hasDefusing;
    int   flashDuration;
    int   flashAlpha;
    /// 1-CT 2-T
    int   team;
    BYTE  activeWeaponID[4];
    BYTE  myWeaponTable[16];// 0x4
    bool  iAlive;

    bool Update(ProcessManager*);
    CBasePlayer();
};

#endif //UNTITLEDWARE_CBASEPLAYER_H