#ifndef IFOVCHANGER_H
#define IFOVCHANGER_H
#include "csgo_signatures.h"
#include "Player.h"
#include "globals.h"

bool iFovChanger() {
    Player local;

    while (true)
    {
        if (local.isAlive)
        {
            Write<int>(Global::signatures::localPlayer+hazedumper::netvars::m_iDefaultFOV, 130);
            Write<int>(Global::signatures::localPlayer+hazedumper::netvars::m_bIsScoped, -9);
        }
    }
}

#endif //IFOVCHANGER_H
