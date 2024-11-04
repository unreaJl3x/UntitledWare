#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

#include "csgo_signatures.h"


class Player {
public:
    int  iHealth;
    int  iArmor;
    int  fFlags;

    bool flFlashed;
    bool isScoped;
    bool bHasDefuser;
    bool bHasHelmet;
    bool bInReload;
    bool isAlive = true;
    int  iFov;
    Player();
    bool updateDate();
};



#endif
