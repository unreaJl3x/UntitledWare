#include "globals.h"
Game csgo;

namespace Global{
    namespace signatures
    {
        uintptr_t client;
        uintptr_t localPlayer;
    }

    void Init(string nameexe, string nameapp)
    {
        csgo = *(new Game(nameexe,nameapp));
    }
}