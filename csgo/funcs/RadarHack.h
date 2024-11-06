#ifndef RADARHACK_H
#define RADARHACK_H
#include "globals.h"
#include "mem.h"
#define PLAYERCOUNT 10
using namespace Memory;

namespace RadarHack {
    bool main()
    {
        Player allPlayers[PLAYERCOUNT-1];

        while (true)
        {
            for (int i = 1; i < PLAYERCOUNT-1; i++)
            {
                allPlayers[i-1] = Player( Read<uintptr_t>(Global::signatures::clientAddr+hazedumper::signatures::dwEntityList+(0x10*(i))) );
                allPlayers[i-1].updateDate();

                if (allPlayers[i-1].iTeamNum != Global::signatures::Players::localPlayer.iTeamNum)
                {
                    Write<int>(allPlayers[i-1].CBaseAddress+hazedumper::netvars::m_bSpotted, 1);
                }
            }
        }

        return true;
    }
    void returned () {}
}

#endif
