#include "globalDate.h"

namespace GLOBAL {
    namespace GameDate {
        CBasePlayer* players;
        int playerCount;
    }
    namespace AppDate{
         HANDLE pHandle;
         DWORD pID;
    }
    namespace Addrs {
        uintptr_t client;
    }
}