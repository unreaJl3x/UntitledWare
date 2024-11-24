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
    cout << cl<<endl;
    lc = Read<uintptr_t>(cl + hazedumper::signatures::dwLocalPlayer);
    en = Read<uintptr_t>(cl + hazedumper::signatures::dwEntityList);

    uintptr_t addree=0x0;
    HANDLE h = OpenProcess(PROCESS_ALL_ACCESS,NULL,csgo.pID);
    ReadProcessMemory(h, LPVOID(cl + hazedumper::signatures::dwLocalPlayer),&addree,sizeof(uintptr_t),NULL);
    cout << lc <<"  "<<en<<" "<<addree<<endl;
    lc=addree;

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
