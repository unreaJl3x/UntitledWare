#include "globals.h"
Game csgo;
namespace Global{
    void Init(HANDLE h, DWORD id, uintptr_t client) {
        csgo = *(new Game(h, id, client));
    }
}