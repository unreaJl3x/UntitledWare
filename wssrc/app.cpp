#include "app.h"

App::App() {
    nameApp = "UntitledWare";
    version = "test00";

}

void App::SetHeader() {
    SetConsoleTitleA((App::nameApp+" "+App::version+"|"+(lisensed?"Licensed":"UnLicensed")).c_str());
}

