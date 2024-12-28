#include "app.h"

#define pm ProcessManager

App::App(string nameApp, string nameExe, string iCNW) {
    this->nameApp = nameApp;
    this->nameExe = nameExe;
    this->IpClassNameWindow = iCNW;

    this->pId = pm::GetPID(&nameExe);
    if (pId == -1) {
        running = false;
        Output::print("'" + nameApp + "' have is Invalid pid.", false, "main");
        return;
    }
    this->pHandle = pm::GetHandle(pId);
    if (pHandle == INVALID_HANDLE_VALUE) {
        running = false;
        Output::print("'" + nameApp + "' invalid handle", false, "main");
        return;
    }

    this->hwnd = pm::GetWindowHandle(&IpClassNameWindow, &nameApp);
}

void App::SetHeader(string text) {
    SetWindowTextA(this->hwnd, text.c_str());
}

bool App::isRunning() { return running; }