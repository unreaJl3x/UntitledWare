#include "Player.h"

Player::Player(uintptr_t addr)
{
    this->addr = addr;
    Player::updateDate();
    return;
}

bool Player::updateDate()
{
    iHealth = Read<int>(addr+hazedumper::netvars::m_iHealth);
    iArmor = Read<int>(addr+hazedumper::netvars::m_ArmorValue);
    fFlags = Read<int>(addr+hazedumper::netvars::m_fFlags);
    flFlashDuration = Read<bool>(addr+hazedumper::netvars::m_flFlashDuration);
    isScoped = Read<bool>(addr+hazedumper::netvars::m_bIsScoped);
    bHasDefuser = Read<bool>(addr+hazedumper::netvars::m_bHasDefuser);
    bHasHelmet = Read<bool>(addr+hazedumper::netvars::m_bHasHelmet);
    bInReload = Read<bool>(addr+hazedumper::netvars::m_bInReload);
    iFov = Read<int>(addr+hazedumper::netvars::m_iDefaultFOV);
    isAlive = iHealth > 0;

    return true;
}

