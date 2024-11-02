#include "local.h"

void UntitledWare::Test::local() {
    const uintptr_t localAddr = csgo.localPlayerAddress;
    cout << "pid " << csgo.pID<<endl;
    while(true) {
        cout << "LOCAL PLAYER|| health("<<Read<int>(csgo.pHandle,localAddr+hazedumper::netvars::m_iHealth)<<"),"
             << " Armore ("<<Read<int>(csgo.pHandle, localAddr+hazedumper::netvars::m_ArmorValue)<<"), "
             <<" Position x("<< Read<int>(csgo.pHandle,localAddr+hazedumper::netvars::m_vecOrigin) <<") y() z()"
             <<" Collision "<<Read<int>(csgo.pHandle, localAddr+hazedumper::netvars::m_Collision)
             <<" Collision Group "<<Read<int>(csgo.pHandle, localAddr+hazedumper::netvars::m_CollisionGroup)
             <<" Valve DS" << Read<int>(csgo.pHandle, localAddr+hazedumper::netvars::m_bIsValveDS)<<""
             <<"\r";
    }
}