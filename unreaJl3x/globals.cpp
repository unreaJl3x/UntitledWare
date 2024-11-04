#include "globals.h"
Game csgo;

namespace Global{
    namespace signatures
    {
        uintptr_t client;
    }

    void Init(string nameexe, string nameapp)
    {
        csgo = *(new Game(nameexe,nameapp));
    }
}