#include "hack.h"

#include <string>
#include <thread>

#include "csgo_signatures.h"
#include "funcs/iFovChanger.h"

void hackIt(HANDLE handle) {
    Global::signatures::client = Proc::GetModuleAddress("client.dll");
    if (Global::signatures::client<=1) {return;}

    Global::signatures::localPlayer = Read<uintptr_t>(Global::signatures::client+hazedumper::signatures::dwLocalPlayer);

    thread FovChanger(iFovChanger);

    while(csgo.CheckValidApp())
    {

        /*if (localAddr!=0)
        {
            static int health = Read<int>(localAddr+0x100);

        }*/


    }

    return;
}
