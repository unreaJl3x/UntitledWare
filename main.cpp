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
#include "dx_interface/dxOverlay.h"
#include "dx_interface/dxRender.h"
using namespace std;

bool HaveADooplicant(string nameApp) {
    vector<PROCESSENTRY32> pEntres = ProcessManager::GetAllProcessEntry(&nameApp);
    return pEntres.size() >= 2;
}

#define KEYOFF VK_END

#define W_WIDTH 350
#define W_HEIGHT 300

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
    MSG _msg;
    ZeroMemory(&_msg,sizeof(_msg));
    dxRender rend = over.CreateRender();

    D3DCOLOR RainBow = dxRender::COLOR::RED;
    D3DCOLOR BACKGROUND = dxRender::COLOR::VERYBLACKGRAY;
    RECT menuRect(0,0,W_WIDTH,W_HEIGHT);

    rend.addTexture(new RECT(menuRect.left,menuRect.top,menuRect.right,30),0);
    rend.addTexture(&menuRect,1);

    do {
        if ( PeekMessage( &_msg, over.GetWindowHandle( ), NULL, NULL, PM_REMOVE ) ) {
            TranslateMessage( &_msg );
            DispatchMessage( &_msg );
        }
        unique_lock lock(_m);

        RainBow = dxRender::COLOR::Rainbow(RainBow);
        rend.beginRender();

        rend.drawBox(&menuRect, BACKGROUND, new char[2]{DB_OUTLINE, DB_FILLED}, vector<int>{1});
        rend.drawBox(&menuRect, RainBow);
        rend.drawBox(&menuRect, RainBow, new char[1]{DB_FILLED}, vector<int>{0});
        rend.drawText(new POINT{menuRect.left,menuRect.top},"UntitledWare",BACKGROUND,25);
        rend.drawLine(new POINT{menuRect.left+30,menuRect.top},new POINT{menuRect.left+30,menuRect.bottom},RainBow);
        bool r;
        rend.Button(new RECT(menuRect.left+5,menuRect.top+60,menuRect.left+25,menuRect.top+80),dxRender::COLOR::PINK,&r);
        if (r) {cout<<"work"<<endl;}
        rend.endRender();
        rend.DragMenu(&menuRect);

        this_thread::sleep_for(chrono::milliseconds(1));
    } while(!GetAsyncKeyState(VK_END));

    Output::print("Exit on application.", true, "main");
    getchar();
    return EXIT_SUCCESS;
}

