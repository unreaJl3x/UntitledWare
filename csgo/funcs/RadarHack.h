#ifndef RADARHACK_H
#define RADARHACK_H

#include "funcs.h"

#define allPlayers Global::signatures::Players::allPlayers

namespace RadarHack {
    bool main()
    {
        while (true) {
            if (configSys.dateRadarHack.active) {
                for (int i = 1; i < 10 - 1; i++) {
                    allPlayers[i - 1] = Player(Read<uintptr_t>(
                            Global::signatures::clientAddr + hazedumper::signatures::dwEntityList + (0x10 * (i))));
                    allPlayers[i - 1].updateDate();

                    if (allPlayers[i - 1].iTeamNum != Global::signatures::Players::localPlayer.iTeamNum) {
                        Write<int>(allPlayers[i - 1].CBaseAddress + hazedumper::netvars::m_bSpotted, 1);
                    }
                }
            }
            SLEEP
        }
        return true;
    }
    void returned () {return;}
}

#endif
