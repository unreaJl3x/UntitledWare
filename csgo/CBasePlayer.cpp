#include "CBasePlayer.h"
#include <string>

CBasePlayer::CBasePlayer(uintptr_t addr) {
    this->localAddress = addr;

    addOffset("health", DUMP::m_iHealth, 0);
    addOffset("armore", DUMP::m_ArmorValue, 0);
    addOffset("flags", DUMP::m_fFlags, 0);
    addOffset("isscoped", DUMP::m_bIsScoped, 0);
    addOffset("isreload", DUMP::m_bInReload, 0);
    addOffset("hasdefuser", DUMP::m_bHasDefuser, 0);
    addOffset("hasdefusing", DUMP::m_bIsDefusing, 0);
    addOffset("flashduration", DUMP::m_flFlashDuration, 0);
    addOffset("slashalpha", DUMP::m_flFlashMaxAlpha, 0);
    addOffset("team", DUMP::m_iTeamNum, 0);
    addOffset("fov", DUMP::m_iDefaultFOV, 0);
}

void CBasePlayer::addOffset(string key, uintptr_t addr, BYTE var) {
    keys.push_back(key); Date d(var,addr);
    memory[key] = d;
}
