#ifndef CHEATCSGOEXTERNAL_GAME_H
#define CHEATCSGOEXTERNAL_GAME_H

#include <windows.h>
#include <iostream>
using namespace std;

class Game {
public:
        string nameExe;
        string nameApp;
        uintptr_t localPlayerAddress;
        uintptr_t clientDllAddress;
        DWORD pID ;
        HANDLE pHandle;

        Game();
        Game(string, string);

        bool CheckValidApp();
};

#endif //CHEATCSGOEXTERNAL_GAME_H