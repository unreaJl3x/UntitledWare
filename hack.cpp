#include "hack.h"

#include <string>

#include "csgo_signatures.h"

void hackIt(HANDLE handle) {
    static uintptr_t clientDll = Proc::GetModuleAddress("client.dll");
    if (clientDll<=1) {return;}

    while(csgo.CheckValidApp())
    {
        static uintptr_t localAddr = Read<uintptr_t>(clientDll+0x00DEF97C);
        if (localAddr!=0)
        {
            static int health = Read<int>(localAddr+0x100);
            Write<int>(clientDll+, 1);
        }
    }

    return;
}
