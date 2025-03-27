#include "RadarHack.h"

namespace RadarHack {
    void main(HANDLE h, AppCS* csgo, ConfController* cfc)
    {
        CBasePlayer allPlayers[PLAYERCOUNT-1];
        uintptr_t client = ProcessManager::GetModuleAddr("client.dll", csgo->GetProcessId());
        uintptr_t local = ProcessManager::ReadMemory(client+hazedumper::signatures::dwLocalPlayer,4,h);;
        while (true)
        {
            for (int i = 1; i < PLAYERCOUNT-1; i++)
            {
                allPlayers[i-1] = CBasePlayer(ProcessManager::ReadMemory(client+hazedumper::signatures::dwEntityList+(0x10*(i)),4, h), h);
                allPlayers[i-1].Load(vector<string>("spotted","team"));

                if (allPlayers[i-1].memory._map["team"].varible != allPlayers[0].memory._map["team"].varible)
                {
                    ProcessManager::WriteMemory(allPlayers[i-1].GetAddr() + hazedumper::netvars::m_bSpotted, 4, new int(1), h);
                }
            }
        }

        return;
    }
}
