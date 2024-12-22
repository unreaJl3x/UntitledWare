#include "CSGOCheatFuncsStarter.h"

CBasePlayer* pl;
ProcessManager* _pm;
Output* _out;

void updatePlayersDate() {
    //pl->Update();
}

void updatePlayersList() {
    GLOBAL::GameEntity::players.clear();
    GLOBAL::GameEntity::playerCount = 0;
    unsigned __int8 i = 0;
    while (_pm->ReadMemory<sizeof(uintptr_t)>(GLOBAL::Addrs::entityList+0x10*i) != 0) {
        GLOBAL::GameEntity::players.push_back(new CBasePlayer(_pm, _out, GLOBAL::Addrs::entityList+0x10*i));
        i++;
        GLOBAL::GameEntity::playerCount++;
    }
}

void CSGOCheatFuncsStarter(FileSystem* fs, Output* out, ProcessManager* pm) {
    _pm = pm;
    _out = out;

    GLOBAL::cfgSys = new ConfigSys(fs,out);
    GLOBAL::AppDate::pHandle = pm->app.pHandle;
    GLOBAL::AppDate::pID = pm->app.pId;
    GLOBAL::Addrs::client = pm->GetModuleAddr("client.dll");

    while(true) {
        if (false) {
            updatePlayersList();
        } else {
            for (int i = 0; i < GLOBAL::GameEntity::playerCount; i++) {
                pl = GLOBAL::GameEntity::players[i];
                thread updPl(updatePlayersDate);
            }
        }

    }
}

