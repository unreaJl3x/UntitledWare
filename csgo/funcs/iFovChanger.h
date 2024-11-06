#ifndef IFOVCHANGER_H
#define IFOVCHANGER_H

#include "funcs.h"

namespace FovChanger
{
    bool main() {
        Player pl;

        while (true)
        {
            if (Global::signatures::Players::localPlayer.isAlive)
            {
                Write<int>(local+hazedumper::netvars::m_iDefaultFOV, 130);
            } else {returned();}
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    }
    void returned() { Write<int>(local+hazedumper::netvars::m_iDefaultFOV, 90); }
}
#endif //IFOVCHANGER_H
