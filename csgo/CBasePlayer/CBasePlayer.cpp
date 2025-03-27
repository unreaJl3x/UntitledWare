#include "CBasePlayer.h"
#include <string>

CBasePlayer::CBasePlayer(uintptr_t addr, HANDLE h) {
    this->addr = addr;
    this->handle = h;
    addOffset("health", DUMP::m_iHealth, 0);
    addOffset("armore", DUMP::m_ArmorValue, 0);
    addOffset("flags", DUMP::m_fFlags, 0);
    addOffset("isscoped", DUMP::m_bIsScoped, 0);
    addOffset("isreload", DUMP::m_bInReload, 0);
    addOffset("hasdefuser", DUMP::m_bHasDefuser, 0);
    addOffset("hasdefusing", DUMP::m_bIsDefusing, 0);
    addOffset("flashduration", DUMP::m_flFlashDuration, 0);
    addOffset("flashalpha", DUMP::m_flFlashMaxAlpha, 0);
    addOffset("team", DUMP::m_iTeamNum, 0);
    addOffset("fov", DUMP::m_iDefaultFOV, 0);
    addOffset("spotted", DUMP::m_bSpotted, 0);
}

void CBasePlayer::addOffset(string key, uintptr_t addr, BYTE var) {
    memory._keys.push_back(key); Date<int> d(var,addr);
    memory._map[key] = d;
}

void CBasePlayer::Load(vector<string> keys) {
    for (string key : keys ) {
        memory._map[key].varible = ProcessManager::ReadMemory(addr+memory._map[key].addr,4,handle);
    }
}

uintptr_t CBasePlayer::GetAddr() {
    return addr;
}
