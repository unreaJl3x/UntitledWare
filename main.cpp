#include <ProcessManager.h>
#include <AppCS.h>
#include <FileSystem.h>
#include "CSGOCheatFuncsStarter.h"
int main(int argc, char *argv[]) {
    SetConsoleTitleA("UntitledWare <!/>");
    if (argc > 2) {}
    AppCS csgo;

    if (!csgo.isRunning()) { return -1; }

    Output::print(
            "'" + csgo.nameApp + "'" + " have is id-> " + to_string(csgo.pId) + ", hwnd->"
            + to_string(reinterpret_cast<int>( csgo.hwnd)), 1, "main"
    );

    CSGOCheatFuncsStarter(&csgo);

    Output::print("Exit on application.", true, "main");

    getchar();
    return EXIT_SUCCESS;
}
