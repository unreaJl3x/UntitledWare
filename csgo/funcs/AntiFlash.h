#ifndef ANTIFLASH_H
#define ANTIFLASH_H

#include "funcs.h"
namespace AntiFlash
{
    bool main() {
        Player pl;

        while (true)
        {
            if (pl.isAlive)
            {
                Write<int>(local + hazedumper::netvars::m_flFlashMaxAlpha, 0);
            }
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    }
    void returned(){ Write<int>(local + hazedumper::netvars::m_flFlashMaxAlpha, 1132396544); }
}
#endif
