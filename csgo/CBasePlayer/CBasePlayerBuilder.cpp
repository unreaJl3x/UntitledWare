#include "CBasePlayerBuilder.h"

vector<CBasePlayer> CBasePlayerBuilder::GetPlayerList(AppCS* csgo) {
    vector<CBasePlayer> players;

    for (int playerNum = 0; playerNum < csgo->GetPlayerCountInMatch(); playerNum++) {
        uintptr_t playerPoint = ProcessManager::ReadMemory(csgo->clientAddress + hazedumper::signatures::dwEntityList + (0x10 * playerNum), sizeof(int), csgo->GetProcessHandle());
        players.push_back(*new CBasePlayer());
        for (string memoryKey : players[playerNum].keys) {
            players[playerNum].memory[memoryKey].varible = ProcessManager::ReadMemory(
                    (playerPoint + players[playerNum].memory[memoryKey].addr),
                    sizeof(int),
                    csgo->GetProcessHandle()
            );
        }
    }

    return players;
}