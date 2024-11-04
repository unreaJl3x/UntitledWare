#ifndef CHEATCSGOEXTERNAL_GLOBALS_H
#define CHEATCSGOEXTERNAL_GLOBALS_H

#include "game.h"

extern Game csgo;
namespace Global{
    namespace signatures
    {
        extern uintptr_t client;
        extern uintptr_t localPlayer;
    }
    void Init(string,string);
}
#endif //CHEATCSGOEXTERNAL_GLOBALS_H
