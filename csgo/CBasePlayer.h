#ifndef UNTITLEDWARE_CBASEPLAYER_H
#define UNTITLEDWARE_CBASEPLAYER_H

#include <iostream>
#include <windows.h>

#include "ProcessManager.h"
#include "csgo_signatures.h"
using namespace std;

class CBasePlayer {
private:
    uintptr_t addr;
public:
    int   iHealth;
    int   iArmore;
    bool  onGround;
    bool  isScoped;
    bool  isReload;
    bool  hasDefuser;
    bool  hasHelmet;
    int   flashDuration;
    int   flashAlpha;
    int   team; // 2-T
    BYTE activeWeaponID[4];
    BYTE myWeaponTable[16];// 0x4
    bool  iAlive;

    bool Update(ProcessManager*);
};

#endif //UNTITLEDWARE_CBASEPLAYER_H