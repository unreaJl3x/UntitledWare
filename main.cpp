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


void returnColor(D3DCOLOR _color) {
    const int modifires_ARGB[4] = {16777216,65536,256,1};
    __int64 color = _color;
    int count,u = 0;
    int en[4]{0,0,0,0};

    for (int mod : modifires_ARGB) {
        do {
            cout << "mod"<<mod;
            count++;
            color -= mod;
            cout<<color<<endl;
        } while( color > 0);
        color += mod;
        cout<<"COlOR "<<count<<endl;
        count=0;
        en[u]=count;
        u++;
    }
    cout << "NEW COLOR ARGB - "<<en[0]<<"X"<<en[1]<<"X"<<en[2]<<"X"<<en[3]<<endl;
}

int main(int argc, char *argv[]) {
    SetConsoleTitleA("UntitledWare <!/>");
    if (HaveADooplicant(basic_string(argv[0]).erase(0, basic_string(argv[0]).find_last_of('\\') + 1))) {
        Output::printMSG("Programm is already running!","UntitledWare");
        return EXIT_FAILURE;
    }
    returnColor(dxRender::COLOR::RED);
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
    mutex _mutex;

    MSG message;
    ZeroMemory(&message,sizeof(message));

    bool run,showMenu,cann = true;
    dxRender rend = over.CreateRender();

    do {
        cann=true;
        if ( PeekMessage( &message, over.GetWindowHandle( ), NULL, NULL, PM_REMOVE ) ) {
            TranslateMessage( &message );
            DispatchMessage( &message );
        }
        unique_lock lock(_mutex);
        if (GetAsyncKeyState(OFFKEY)&cann) { showMenu = !showMenu; cann=false;}

        rend.beginRender();
        //menu
        if (showMenu) {
            D3DCOLOR ac = dxRender::COLOR::RED;
            D3DCOLOR bg = dxRender::COLOR::GRAY;

            RECT r(0, 0, 320, 230);
            rend.drawBox(r, bg, true);
            rend.drawBox(r, ac, false);
            rend.drawText({r.left, r.top}, "UntitledWare", ac, 25);
            rend.drawLine({r.left+25,r.top},{r.left+25,r.bottom},ac);
            rend.drawLine({r.left,r.top+12},{r.right,r.top+12},ac);
            D3DCOLOR c = dxRender::COLOR::Rainbow(c);
        }
        //menu
        rend.endRender();
        this_thread::sleep_for(chrono::milliseconds(1));
    } while(run | message.message != WM_QUIT);



    Output::print("Exit on application.", true, "main");
    getchar();
    return EXIT_SUCCESS;
}

