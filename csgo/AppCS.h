#ifndef UNTITLEDWARE_APPCS_H
#define UNTITLEDWARE_APPCS_H

#include <map>
#include <vector>

#include "app.h"
#include "ProcessManager.h"
#include "hazedumper.h"
#include "csgo/CBasePlayer/CBasePlayer.h"

class AppCS : public App {
public:
    uintptr_t clientAddress;
    int GetPlayerCountInMatch();

    vector<CBasePlayer> GetPlayers();

    AppCS() : App("Counter-Strike: Global Offensive - Direct3D 9", "csgo.exe", "Valve001") {
        clientAddress = ProcessManager::GetModuleAddr("client.dll", GetProcessId());
    };
};


#endif
