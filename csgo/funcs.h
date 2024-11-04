#ifndef FUNCS_H
#define FUNCS_H

#define local Global::signatures::localPlayer

#include "csgo_signatures.h"
#include "Player.h"
#include "globals.h"
#include "mem.h"
using namespace Memory;

namespace FovChanger
{
    bool main();
    void returned();
}

namespace AntiFlash
{
    bool main();
    void returned();
}

#endif //FUNCS_H
