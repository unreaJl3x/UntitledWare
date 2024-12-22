#ifndef UNTITLEDWARE_GLOBALDATE_H
#define UNTITLEDWARE_GLOBALDATE_H

#include "CBasePlayer.h"
#include "ConfigSys.h"

namespace GLOBAL {

    extern ConfigSys* cfgSys;
    namespace AppDate {
        extern DWORD pID;
        extern HANDLE pHandle;
    }
    namespace Addrs {
        extern uintptr_t client;
        extern uintptr_t entityList;
    }
    namespace GameEntity {
        extern unsigned __int8 playerCount;
        extern vector<CBasePlayer*> players;
    }
}

#endif //UNTITLEDWARE_GLOBALDATE_H
