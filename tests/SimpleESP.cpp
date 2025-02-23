#include "SimpleESP.h"
#include "csgo/CBasePlayer/CBasePlayer.h"

void SimpleESP(AppCS* csgo) {
    vector<CBasePlayer> players;
    bool isRunning = true;

    while(isRunning) {
        int countInMatch = csgo->GetPlayerCountInMatch();
        if (countInMatch == 0) {
            cout << "Client in lobby." << "\r";
            return;
        }

        players = csgo->GetPlayers();
        for (int playerNum = 0; playerNum < csgo->GetPlayerCountInMatch(); playerNum++) {
            cout << "   | " << (players[playerNum].memory["team"].varible == 2 ? "T Player " : "CT Player ") << " "
                 << playerNum << "DEFUSING(" << (players[playerNum].memory["hasdefusing"].varible ? "Y" : "N")
                 << ") have a " << players[playerNum].memory["health"].varible << "HP    ";
        }
        cout << "\r";
        if (GetAsyncKeyState(VK_F10)) {
            !isRunning;
        }
    }
}