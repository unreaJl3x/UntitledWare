#include "globals.h"
#include "Proc.h"
Game csgo("csgo.exe","Counter-Strike:GlobalOffensive");
ConfigSys configSys("C:\\Users\\"+Proc::GetWinUser()+"\\AppData\\Roaming\\UntitledWare\\");

namespace Global{
    namespace signatures
    {
        uintptr_t clientAddr;
        uintptr_t localAddr;
        uintptr_t entityAddr;

        namespace Players
        {
            Player localPlayer; // CBasePlayer example
            Player allPlayers[PLAYERSC-1];
        }
    }

    void UpdateDate() {
        Global::signatures::Players::localPlayer.updateDate();
        for (int i = 0; i < PLAYERSC; i++) {
            Global::signatures::Players::allPlayers[i].updateDate();
        }
        SLEEP
    };
}