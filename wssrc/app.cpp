#include "app.h"

App::App(string nameApp, string nameExe, string version, Output* out) {
    this->out = out;
    this->nameApp = nameApp;
    this->nameExe = nameExe;
    this->version = version;
    //this->pId = pm.GetPID();
    //this->pHandle = pm.GetHandle();
    this->hwnd = pm.GetWindowHandle();
    SetWindowTextA(hwnd,"HUI");
}

void App::SetHeader(string text) {
    SetWindowTextA(this->hwnd,text.c_str());
}

