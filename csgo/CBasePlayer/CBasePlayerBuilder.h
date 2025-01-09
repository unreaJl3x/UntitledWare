#ifndef UNTITLEDWARE_CBASEPLAYERBUILDER_H
#define UNTITLEDWARE_CBASEPLAYERBUILDER_H

#include "CBasePlayer.h"
#include "csgo/AppCS.h"

class CBasePlayerBuilder {
public:
    static vector<CBasePlayer> GetPlayerList(AppCS*);
};


#endif //UNTITLEDWARE_CBASEPLAYERBUILDER_H
