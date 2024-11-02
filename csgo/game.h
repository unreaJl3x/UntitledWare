#ifndef CHEATCSGOEXTERNAL_GAME_H
#define CHEATCSGOEXTERNAL_GAME_H

#include <windows.h>
#include <iostream>

#include "csgo_signatures.h"
#include "mem.h"
using namespace std;
using namespace Memory;

class Game {
public:
        uintptr_t localPlayerAddress;
        uintptr_t clientDllAddress;
        DWORD pID ;
        HANDLE pHandle;

        Game();
        Game(HANDLE handle, DWORD id, uintptr_t client);
        bool isGrounded();
        void GetActiveWeapon();
};

#endif //CHEATCSGOEXTERNAL_GAME_H
