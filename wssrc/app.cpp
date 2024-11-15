#include "app.h"

App::App(string nameApp, string nameExe, string version) {
    this->nameApp = nameApp;
this->nameExe = nameExe;
    this->version = version;
}

void App::SetHeader(string text) {
    SetWindiwTitleA(this->hwnd,text.c_str());
}

