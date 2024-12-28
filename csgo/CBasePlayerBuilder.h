#ifndef UNTITLEDWARE_CBASEPLAYERBUILDER_H
#define UNTITLEDWARE_CBASEPLAYERBUILDER_H

#include "CBasePlayer.h"

class CBasePlayerBuilder {
public:
    static CBasePlayer GetPlayer(int, uintptr_t, HANDLE h);
};


#endif //UNTITLEDWARE_CBASEPLAYERBUILDER_H
