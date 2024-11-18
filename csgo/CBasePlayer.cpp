#include "CBasePlayer.h"

bool CBasePlayer::Update(ProcessManager* pm) {
     iHealth = pm->Read<int>(addr + hazedumper::netvars::m_iHealth);
     iArmore = pm->Read<int>(addr + hazedumper::netvars::m_ArmorValue);
     onGround = pm->Read<int>(addr + hazedumper::netvars::m_fFlags)==257;
     isScoped = pm->Read<int>(addr + hazedumper::netvars::m_bIsScoped)==1;
     isReload;
     team = pm->Read<int>(addr + hazedumper::netvars::m_iTeamNum);
     hasDefuser = pm->Read<int>(addr + hazedumper::netvars::m_bHasDefuser);
     hasHelmet = pm->Read<int>(addr + hazedumper::netvars::m_bHasHelmet);
     flashDuration = pm->Read<int>(addr + hazedumper::netvars::m_flFlashDuration);
     flashAlpha = pm->Read<int>(addr + hazedumper::netvars::m_flFlashMaxAlpha);
     for(int i = 0; i < 16;i++) {
        myWeaponTable[i] = pm->Read<BYTE>(addr+ hazedumper::netvars::m_hMyWeapons);
     }
     iAlive = pm->Read<int>(addr + hazedumper::netvars::m_lifeState)==0;

    return true;
}