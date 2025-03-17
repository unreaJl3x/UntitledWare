#ifndef RADARHACK_H
#define RADARHACK_H

#include "ConfController.h"
#include "wssrc/ProcessManager.h"
#include "csgo/hazedumper.h"

namespace FovChanger {
    bool main(HANDLE h,ConfController* cfc, DWORD pid)
    {
        uintptr_t client = ProcessManager::GetModuleAddr("client.dll", pid);
        uintptr_t local = ProcessManager::ReadMemory(client+hazedumper::signatures::dwLocalPlayer,4,h);;
        while (true)
        {
            if (*cfc->GetLinkB("FovChanger.active") == true) {
                ProcessManager::WriteMemory(local+hazedumper::netvars::m_iDefaultFOV,4, cfc->GetLinkI("FovChanger.fovValue"), h);
            } else {ProcessManager::WriteMemory(local+hazedumper::netvars::m_iDefaultFOV,4, cfc->GetLinkI("FovChanger.fovValueD"), h);}
        }
        return true;
    }
    void returned () {}
}

#endif