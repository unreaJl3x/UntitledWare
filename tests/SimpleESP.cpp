#include "SimpleESP.h"


void SimpleESP(AppCS* csgo, ConfController* cfc) {
    vector<CBasePlayer> players;
    bool isRunning = true;

    while(isRunning) {
        int countInMatch = csgo->GetPlayerCountInMatch();
        if (countInMatch == 0) {
            cout << "Client in lobby." << "\r";
            return;
        } else if (*cfc->GetLinkB("RadarHack.active")) {
            players = csgo->GetPlayers();
            for (int playerNum = 0; playerNum < csgo->GetPlayerCountInMatch(); playerNum++) {
                cout << "   | " << (players[playerNum].memory["team"].varible == 2 ? "T Player " : "CT Player ") << " "
                     << playerNum << "DEFUSING(" << (players[playerNum].memory["hasdefusing"].varible ? "Y" : "N")
                     << ") have a " << players[playerNum].memory["health"].varible << "HP    ";
            }
            cout << "\r";
        }
    }
}