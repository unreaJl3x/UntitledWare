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
    Global::Init("csgo.exe","Counter-Strike:GlobalOffensive");
    csgo.pID = Proc::GetAppDate(csgo.nameExe.c_str()).id;
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
