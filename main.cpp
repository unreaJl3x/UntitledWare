#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <chrono>
#include <thread>
#include <mutex>

#include "wssrc/MenuController.h"
#include "output.h"
#include "csgo/AppCS.h"
#include "dx_interface/dxOverlay.h"
#include "dx_interface/dxRender.h"
using namespace std;

bool HaveADooplicant(string nameApp) {
    vector<PROCESSENTRY32> pEntres = ProcessManager::GetAllProcessEntry(&nameApp);
    return pEntres.size() >= 2;
}

#define KEY_OFF VK_F1
#define MENU_KEY VK_DELETE
int main(int argc, char *argv[]) {
    SetConsoleTitleA("UntitledWare <!/>");

    if (HaveADooplicant(basic_string(argv[0]).erase(0, basic_string(argv[0]).find_last_of('\\') + 1))) {
        Output::printMSG("Programm is already running!","UntitledWare");
        return EXIT_FAILURE;
    }

    AppCS csgo;
    if (!csgo.isRunning()) {
        getchar();
        return EXIT_FAILURE;
    }

    Output::print(
            "'" + csgo.GetAppName() + "'" + " have is id-> " + to_string(csgo.GetProcessId()) + ", hwnd->"
            + to_string(reinterpret_cast<int>(csgo.GetWindowHandle())), 1, "main"
    );

// body
    dxOverlay over(&csgo);
    mutex _m;
    MSG _msg; ZeroMemory(&_msg,sizeof(_msg));

    bool boolMenu = true;
    dxRender rend = over.CreateRender();

    // MC
    MenuController _mc(&over,&rend, &boolMenu, dxRender::COLOR::VERYBLACKGRAY);
    _mc.CreateButton("FirstButton", DEFAULT_WINDOWPARENT, RECT(0,0,30,30), "pink", new char[1]{DB_OUTLINE}, "b1", 5);
    // MC

    do {
        if ( PeekMessage( &_msg, over.GetWindowHandle( ), NULL, NULL, PM_REMOVE ) ) {TranslateMessage( &_msg );DispatchMessage( &_msg );}
        unique_lock lock(_m);
        if (GetAsyncKeyState(MENU_KEY)) { boolMenu = !boolMenu; }

        rend.beginRender();
        _mc.Draw();
        rend.endRender();

        this_thread::sleep_for(chrono::milliseconds(1));
    } while(!GetAsyncKeyState(KEY_OFF) || _msg.message != WM_QUIT);

    Output::print("Exit on application.", true, "main");
    getchar();
    return EXIT_SUCCESS;
}