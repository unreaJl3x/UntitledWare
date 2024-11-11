#ifndef IFOVCHANGER_H
#define IFOVCHANGER_H

#include "funcs.h"

namespace FovChanger
{
    bool main(){
        while (true)
        {
            //cout << "WTF"<<endl;
            if (configSys.dateFovChanger.active)
            {
                cout << "WTF"<<endl;
                Write<int>(local+hazedumper::netvars::m_iDefaultFOV, configSys.dateFovChanger.value);
            } else {returned();}
            SLEEP
        }
    }
    void returned() { Write<int>(local+hazedumper::netvars::m_iDefaultFOV, 90); }
}
#endif //IFOVCHANGER_H
