#include "hack.h"
#include "csgo/funcs/AntiFlash.h"
#include "csgo/funcs/iFovChanger.h"
#include "csgo/funcs/RadarHack.h"

void hackIt() {
    Global::signatures::clientAddr = Proc::GetModuleAddress("client.dll");
    if (Global::signatures::clientAddr<=1) {return;}

    Global::signatures::localAddr = Read<uintptr_t>(Global::signatures::clientAddr+hazedumper::signatures::dwLocalPlayer);
    Global::signatures::Players::localPlayer = Player(Global::signatures::localAddr);

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
