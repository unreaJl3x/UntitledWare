#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"
#include "mem.h"
#include "csgo_signatures.h"
using namespace Memory;

class Player {
private:
    uintptr_t addr;

public:
    int  iHealth;
    int  iArmor;
    int  fFlags;

    bool flFlashDuration;
    bool isScoped;
    bool bHasDefuser;
    bool bHasHelmet;
    bool bInReload;
    bool isAlive = true;
    int  iFov;

    Player() = default;
    Player(uintptr_t);
    bool updateDate();
};



#endif
