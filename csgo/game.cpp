#include "game.h"
#include "mem.h"
#include "csgo_signatures.h"
#include "Proc.h"
using namespace Memory;

Game::Game() = default;

Game::Game(string nameexe, string nameapp)
{
    this->nameExe = nameexe;
    this->nameApp = nameapp;
}

bool Game::CheckValidApp()
{
    pHandle = Proc::OpenHandle();
    bool validate = (pID >= 0) && (pID <= 90000) && (pHandle != INVALID_HANDLE_VALUE);
    return validate;
}
