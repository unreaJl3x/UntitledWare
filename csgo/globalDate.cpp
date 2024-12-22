#include "globalDate.h"

namespace GLOBAL {
    ConfigSys* cfgSys;
    namespace AppDate {
        DWORD pID;
        HANDLE pHandle;
    }
    namespace Addrs {
        uintptr_t client;
        uintptr_t entityList;
    }
    namespace GameEntity {
        unsigned __int8 playerCount;
        vector<CBasePlayer*> players;
    }
}