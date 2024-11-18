#include "app.h"

App::App(string nameApp, string nameExe, string ICNW, Output* outs) {
    out = outs;
    this->nameApp = nameApp;
    this->nameExe = nameExe;
    this->IpClassNameWindow = ICNW;
}

void App::SetHeader(string text) {
    SetWindowTextA(this->hwnd,text.c_str());
}
