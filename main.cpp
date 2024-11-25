//	https://yougame.biz/threads/100325/
//	https://elar.urfu.ru/bitstream/10995/58964/1/978-5-91256-403-1_2018_125.pdf
//	https://yougame.biz/threads/22883/
//	https://yougame.biz/threads/96665/
//	https://www.unknowncheats.me/forum/counterstrike-global-offensive/324767-setupvelocity.html
//	https://github.com/VSES/SourceEngine2007/blob/master/src_main/engine/cl_main.cpp#L1815-L1855

#include <iostream>
#include <string>
#include <windows.h>

#include "unreaJl3x/globals.h"
#include "unreaJl3x/Proc.h"
#include "output.h"
#include "unreaJl3x/security.h"
using namespace std;

int main() {
    SetConsoleTitle("UntitledWare | UnLICENSED");
    csgo.pID = Proc::GetAppDate(csgo.nameExe.c_str()).id;
    csgo.pHandle = Proc::OpenHandle();
    OUTPUT::print((csgo.nameApp + (csgo.pID==4294967295? " is not found.":" have id is "+to_string(csgo.pID))),0,"main");

    if (csgo.CheckValidApp()) {
        if (Proc::GetRunningExempls(Proc::GetAppDate(GetCurrentProcessId()).name)) { ShowWindow(GetConsoleWindow(),SW_HIDE);OUTPUT::print_msg("Programm already running.");return 0; }
        Security sec;
        sec.Start();
    }

    OUTPUT::print("Exit programm", 1, "main");
	getchar();

	return 190;
}
