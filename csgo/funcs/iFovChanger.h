#ifndef IFOVCHANGER_H
#define IFOVCHANGER_H

#include "funcs.h"

namespace FovChanger
{
    bool main(){
        while (true)
        {
            if (configSys.dateFovChanger.active)
            {
                Write<int>(local+hazedumper::netvars::m_iDefaultFOV, configSys.dateFovChanger.value);
            } else {returned();}
            SLEEP
        }
    }
    void returned() { Write<int>(local+hazedumper::netvars::m_iDefaultFOV, 90); }
}
#endif //IFOVCHANGER_H
