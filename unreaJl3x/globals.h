#ifndef CHEATCSGOEXTERNAL_GLOBALS_H
#define CHEATCSGOEXTERNAL_GLOBALS_H

#include "game.h"
#include "Player.h"

extern Game csgo;
namespace Global{
    namespace signatures
    {
        extern uintptr_t clientAddr;    // "client.dll"
        extern uintptr_t localAddr;     // "client.dll" + 0x00DEF97C

        namespace Players
        {
            extern Player localPlayer;
        }
    }
    void Init(string,string);
}
#endif //CHEATCSGOEXTERNAL_GLOBALS_H
