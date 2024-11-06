#include "Player.h"
#include "mem.h"
using namespace Memory;

Player::Player(uintptr_t addr)
{
    this->CBaseAddress = addr;
    Player::updateDate();
}

bool Player::updateDate()
{
    iHealth = Read<int>(CBaseAddress+hazedumper::netvars::m_iHealth);
    iArmor = Read<int>(CBaseAddress+hazedumper::netvars::m_ArmorValue);
    fFlags = Read<int>(CBaseAddress+hazedumper::netvars::m_fFlags);
    iTeamNum = Read<int>(CBaseAddress+hazedumper::netvars::m_iTeamNum);
    flFlashDuration = Read<bool>(CBaseAddress+hazedumper::netvars::m_flFlashDuration);
    isScoped = Read<bool>(CBaseAddress+hazedumper::netvars::m_bIsScoped);
    bHasDefuser = Read<bool>(CBaseAddress+hazedumper::netvars::m_bHasDefuser);
    bHasHelmet = Read<bool>(CBaseAddress+hazedumper::netvars::m_bHasHelmet);
    bInReload = Read<bool>(CBaseAddress+hazedumper::netvars::m_bInReload);
    iFov = Read<int>(CBaseAddress+hazedumper::netvars::m_iDefaultFOV);
    spotted = Read<int>(CBaseAddress+hazedumper::netvars::m_bSpotted);
    isAlive = iHealth > 0;

    return true;
}



