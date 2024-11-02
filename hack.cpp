#include "hack.h"
#include "globals.h"

void hack(HANDLE h, DWORD pID) {
    const uintptr_t clientDllAddress= Proc::GetModuleAddress(pID,(char*)"client.dll");
    const uintptr_t localAddr = Read<uintptr_t>(h, clientDllAddress+hazedumper::signatures::dwLocalPlayer);
    Global::Init(h,pID,clientDllAddress);

    UntitledWare::Misc::Bunnyhope();
    UntitledWare::Test::local();

    return;
}