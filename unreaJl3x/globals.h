#ifndef CHEATCSGOEXTERNAL_GLOBALS_H
#define CHEATCSGOEXTERNAL_GLOBALS_H


#include <thread>
#include <chrono>
#include <iostream>
#include <vector>

#include "game.h"
#include "Player.h"
#include "configSys.h"

#define PLAYERSC 10
#define SLEEP this_thread::sleep_for(chrono::milliseconds(10));

using namespace std;

extern ConfigSys configSys;
extern Game csgo;

namespace Global{

    namespace signatures
    {
        extern uintptr_t clientAddr;    // "client.dll"
        extern uintptr_t localAddr;     // "client.dll" + 0x00DEF97C
        extern uintptr_t entityAddr;     // "client.dll" + 0x04E051DC

        namespace Players
        {
            extern Player localPlayer;
            extern Player allPlayers[PLAYERSC-1];
        }
    }
    void UpdateDate();
}
#endif //CHEATCSGOEXTERNAL_GLOBALS_H
