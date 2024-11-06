#include "hack.h"
#include "csgo/funcs/AntiFlash.h"
#include "csgo/funcs/iFovChanger.h"
#include "csgo/funcs/RadarHack.h"

#define cl Global::signatures::clientAddr
#define lc Global::signatures::localAddr

void hackIt() {
    cl = Proc::GetModuleAddress("client.dll");
    if (cl <= 1) {OUTPUT::print("Cannot reading addres for 'client.dll'",2,"hackIT");return;}

    lc = Read<uintptr_t>(cl + hazedumper::signatures::dwLocalPlayer);
    Global::signatures::Players::localPlayer = Player(lc);

    thread FovChanger(FovChanger::main);
    //thread AntiFlashs(AntiFlash::main);
    thread RadarHack(RadarHack::main);

    while(true)
    {
        Global::signatures::Players::localPlayer.updateDate();

        this_thread::sleep_for(chrono::milliseconds(100));
    }
    return;
}
