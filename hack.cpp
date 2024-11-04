#include "hack.h"

#include <thread>

#include "csgo_signatures.h"
#include "funcs/AntiFlash.h"
#include "funcs/iFovChanger.h"

void hackIt(HANDLE handle) {
    Global::signatures::client = Proc::GetModuleAddress("client.dll");
    if (Global::signatures::client<=1) {return;}

    Global::signatures::localPlayer = Read<uintptr_t>(Global::signatures::client+hazedumper::signatures::dwLocalPlayer);

    thread FovChanger(FovChanger::main);
    thread AntiFlashs(AntiFlash::main);

    while(csgo.CheckValidApp())
    {

    }

    return;
}
