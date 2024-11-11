#ifndef ANTIFLASH_H
#define ANTIFLASH_H

#include "funcs.h"
namespace AntiFlash
{
    bool main() {
        while (true)
        {
            if (configSys.dateAntiFlash.active)
            {
                Write<int>(local + hazedumper::netvars::m_flFlashMaxAlpha, 0);
            }
            SLEEP
        }
    }
    void returned(){ Write<int>(local + hazedumper::netvars::m_flFlashMaxAlpha, 1132396544); }
}
#endif
