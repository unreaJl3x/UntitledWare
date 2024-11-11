#include "hack.h"
#include "csgo/funcs/AntiFlash.h"
#include "csgo/funcs/iFovChanger.h"
#include "csgo/funcs/RadarHack.h"

#define cl Global::signatures::clientAddr
#define lc Global::signatures::localAddr
#define en Global::signatures::entityAddr

void hackIt() {
    cl = Proc::GetModuleAddress("client.dll");
    if (cl <= 1) {OUTPUT::print("Cannot reading addres for 'client.dll'",2,"hackIT");return;}

    lc = Read<uintptr_t>(cl + hazedumper::signatures::dwLocalPlayer);
    en = Read<uintptr_t>(cl + hazedumper::signatures::dwEntityList);

    Global::signatures::Players::localPlayer = *new Player(Global::signatures::localAddr);
    for(int i = 0; i < 9;i++) {
        allPlayers[i] =  *new Player(Global::signatures::localAddr);
    }

    thread UpdateDate(Global::UpdateDate);
    thread FovChanger(FovChanger::main);
    thread AntiFlashs(AntiFlash::main);
    thread RadarHack(RadarHack::main);

    while(true)
    {
        SLEEP
    }
    return;
}
