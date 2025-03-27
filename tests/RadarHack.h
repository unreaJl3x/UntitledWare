#ifndef RADARHACK_H
#define RADARHACK_H

#define PLAYERCOUNT 10
#include "csgo/CBasePlayer/CBasePlayer.h"
#include "csgo/AppCS.h"
#include "ConfController.h"

namespace RadarHack {
    void main(HANDLE h, AppCS* csgo, ConfController* cfc);
}
#endif