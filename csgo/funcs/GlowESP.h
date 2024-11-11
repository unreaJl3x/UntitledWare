#ifndef UNTITLEDWARE_GLOWESP_H
#define UNTITLEDWARE_GLOWESP_H

#define REDADDR 0x8
#define GREENADDR 0xC
#define BLUEADDR 0x10
#define ALPHAADDR 0x14
#define IDKWHARITIT2 0x28
#define IDKWHARITIT 0x27

#include "funcs.h"

namespace GlowESP {
    bool main() {
        uintptr_t glowObjectManager = Read<uintptr_t>(client+hazedumper::signatures::dwGlowObjectManager);


        while(true) {
            if (configSys.dateGlowESP.active) {
                for(int i = 0;i<9;i++) {
                    int glowIndex = Read<int>(Global::signatures::Players::allPlayers[i].CBaseAddress +hazedumper::netvars::m_iGlowIndex);
                    Write<int>(glowObjectManager+(glowIndex*0x38)+REDADDR,Global::signatures::Players::allPlayers[i].iTeamNum==Global::signatures::Players::localPlayer.iTeamNum?configSys.dateGlowESP.TeamRed:configSys.dateGlowESP.EnemyRed);
                    Write<int>(glowObjectManager+(glowIndex*0x38)+GREENADDR,Global::signatures::Players::allPlayers[i].iTeamNum==Global::signatures::Players::localPlayer.iTeamNum?configSys.dateGlowESP.TeamGreen:configSys.dateGlowESP.EnemyGreen);
                    Write<int>(glowObjectManager+(glowIndex*0x38)+BLUEADDR,Global::signatures::Players::allPlayers[i].iTeamNum==Global::signatures::Players::localPlayer.iTeamNum?configSys.dateGlowESP.TeamBlue:configSys.dateGlowESP.EnemyBlue);
                    Write<int>(glowObjectManager+(glowIndex*0x38)+ALPHAADDR,Global::signatures::Players::allPlayers[i].iTeamNum==Global::signatures::Players::localPlayer.iTeamNum?configSys.dateGlowESP.TeamAlpha:configSys.dateGlowESP.EnemyAlpha);

                    Write<bool>(glowObjectManager+(glowIndex*0x38)+IDKWHARITIT,true);
                    Write<bool>(glowObjectManager+(glowIndex*0x38)+IDKWHARITIT2,true);
                }
            }
            SLEEP
        }
    }
    void returned() {}
}

#endif //UNTITLEDWARE_GLOWESP_H
