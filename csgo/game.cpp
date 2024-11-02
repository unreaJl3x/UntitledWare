#include "game.h"

Game::Game() = default;

Game::Game(HANDLE handle, DWORD id, uintptr_t client) {
    this->pHandle = handle;
    this->pID = id;
    this->clientDllAddress = client;
    this->localPlayerAddress = Read<uintptr_t>(pHandle, client+hazedumper::signatures::dwLocalPlayer);
}

bool Game::isGrounded() {
    return Read<int>(pHandle, localPlayerAddress) == 257 ? false : true;
}
