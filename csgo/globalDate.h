#ifndef UNTITLEDWARE_GLOBALDATE_H
#define UNTITLEDWARE_GLOBALDATE_H

#include "CBasePlayer.h"
#include "ConfigSys.h"

namespace GLOBAL {
    extern CBasePlayer local;
    extern ConfigSys cfgSys;
    namespace AppDate {
        extern DWORD pID;
        extern HANDLE pHandle;
    }
    namespace Addrs {
        extern uintptr_t client;
    }
}

#endif //UNTITLEDWARE_GLOBALDATE_H
