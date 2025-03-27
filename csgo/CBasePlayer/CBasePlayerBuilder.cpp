#include "CBasePlayerBuilder.h"

vector<CBasePlayer> CBasePlayerBuilder::GetPlayerList(AppCS* csgo) {
    vector<CBasePlayer> players;

    for (int playerNum = 0; playerNum < csgo->GetPlayerCountInMatch(); playerNum++) {
        uintptr_t playerPoint = ProcessManager::ReadMemory(csgo->clientAddress + hazedumper::signatures::dwEntityList + (0x10 * playerNum), sizeof(int), csgo->GetProcessHandle());
        players.push_back(*new CBasePlayer(playerPoint, csgo->GetProcessHandle()));
        players[playerNum].Load(vector<string>{"health","team","hasdefusing"});
    }

    return players;
}