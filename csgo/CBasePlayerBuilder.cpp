#include "CBasePlayerBuilder.h"

CBasePlayer CBasePlayerBuilder::GetPlayer(int playerNum, uintptr_t addr, HANDLE h) {
    CBasePlayer pl(ProcessManager::ReadMemory(addr+0x10*playerNum,4,));
    pl
}