#include <iostream>
#include <string>
#include <windows.h>

#include "hack.h"
#include "unreaJl3x/globals.h"
#include "unreaJl3x/Proc.h"
#include "output.h"
using namespace std;

int main() {
    Global::Init("csgo.exe","Counter-Strike:GlobalOffensive");
    csgo.pID = Proc::GetPid();

    OUTPUT::print((csgo.nameApp+" have id is "+to_string(csgo.pID)),0,"main");

    if (csgo.CheckValidApp()) {
        if (Proc::FindProcess(Proc::GetCurrentProcessName())>=2) { ShowWindow(GetConsoleWindow(),0);OUTPUT::print_msg("Programm already running.");return 0; }
        // run mainprocess hack
        hackIt();
    }

    OUTPUT::print("Exit programm", 1, "main");
	getchar();

	return 190;
}
