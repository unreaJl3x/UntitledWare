#include "CBasePlayer.h"
#include <string>

CBasePlayer::CBasePlayer() {
    addOffset("health", DUMP::m_iHealth);
    addOffset("armore", DUMP::m_ArmorValue);
    addOffset("flags", DUMP::m_fFlags);
    addOffset("isscoped", DUMP::m_bIsScoped);
    addOffset("isreload", DUMP::m_bInReload);
    addOffset("hasdefuser", DUMP::m_bHasDefuser);
    addOffset("hasdefusing", DUMP::m_bIsDefusing);
    addOffset("flashduration", DUMP::m_flFlashDuration);
    addOffset("slashalpha", DUMP::m_flFlashMaxAlpha);
    addOffset("team", DUMP::m_iTeamNum);
    addOffset("fov", DUMP::m_iDefaultFOV);
}

void CBasePlayer::addOffset(string key, uintptr_t adr) {
    keys.push_back(key);
    addrsMemory[key] = adr;
}

bool CBasePlayer::Update(ProcessManager* pm) {

     for(int i = 0; i < 16;i++) {
        myWeaponTable[i] = pm->Read<BYTE>(addr+ hazedumper::netvars::m_hMyWeapons);
     }
     iAlive = pm->Read<int>(addr + hazedumper::netvars::m_lifeState)==0;

    return true;
}
