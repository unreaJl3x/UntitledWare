#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

#include "output.h"
#include "csgo/AppCS.h"
#include "dx_interface/dxOverlay.h"
#include "dx_interface/dxRender.h"

using namespace std;

#define OFFKEY VK_END

bool HaveADooplicant(string nameApp) {
    vector<PROCESSENTRY32> pEntres = ProcessManager::GetAllProcessEntry(&nameApp);
    return pEntres.size() >= 2;
}

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
    /*dxOverlay over(&csgo);
    mutex _mutex;

    MSG message;
    ZeroMemory(&message,sizeof(message));

    bool run = true;
    dxRender rend = over.CreateRender();
    string text = "UntitledWare";
    do {
        if ( PeekMessage( &message, over.GetWindowHandle( ), NULL, NULL, PM_REMOVE ) ) {
            TranslateMessage( &message );
            DispatchMessage( &message );
        }
        unique_lock lock(_mutex);
        if (GetAsyncKeyState(OFFKEY)) { !run; }

        rend.beginRender();


        rend.endRender();
        //this_thread::sleep_for(chrono::milliseconds(1));
    } while(run | message.message != WM_QUIT);*/



    Output::print("Exit on application.", true, "main");
    getchar();
    return EXIT_SUCCESS;
}