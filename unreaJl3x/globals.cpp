#include "globals.h"
Game csgo;

namespace Global{
    namespace signatures
    {
        uintptr_t clientAddr;
        uintptr_t localAddr;

        namespace Players
        {
            Player localPlayer; // CBasePlayer example
        }
    }

    void Init(string nameexe, string nameapp)
    {
        csgo = *(new Game(nameexe,nameapp));
    }
}