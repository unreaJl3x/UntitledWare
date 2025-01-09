#include "AppCS.h"
#include <string>
#include "Output.h"
#include "csgo/CBasePlayer/CBasePlayerBuilder.h"
#define maxPlayers 20

int AppCS::GetPlayerCountInMatch() {
    int playersInMatch = 0;
    for(int playerNum = 0; playerNum < maxPlayers; playerNum++) {
        //Output::print("Player"+std::to_string(playerNum)+" have addr "+std::to_string(ProcessManager::ReadMemory((clientAddress + hazedumper::signatures::dwEntityList + (0x10 * playerNum)), 4, pHandle)),false,"GetPlayerCountInMatch");
        if (ProcessManager::ReadMemory((clientAddress+hazedumper::signatures::dwEntityList + (0x10 * playerNum)), sizeof(uintptr_t), GetProcessHandle()) != 0) {
            playersInMatch++;
        } else {break;}
    }
    return playersInMatch;
}

vector<CBasePlayer> AppCS::GetPlayers() {
    return CBasePlayerBuilder::GetPlayerList(this);
}