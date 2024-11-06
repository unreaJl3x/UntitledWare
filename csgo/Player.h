#ifndef PLAYER_H
#define PLAYER_H

#include "csgo_signatures.h"

class Player {
private:


public:
    uintptr_t CBaseAddress;
    int  iHealth;
    int  iArmor;
    int  fFlags;
    int  iTeamNum; // 2 - T; 3 - CT

    bool flFlashDuration;
    bool isScoped;
    bool bHasDefuser;
    bool bHasHelmet;
    bool bInReload;
    bool isAlive = true;
    int  iFov;
    int  spotted;

    Player() = default;
    Player(uintptr_t);
    bool updateDate();
};



#endif
