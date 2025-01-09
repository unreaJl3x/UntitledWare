#include "dxOverlay.h"

#include <iostream>
#include <windows.h>
#include <dwmapi.h>
#include <string>

#include "wssrc/output.h"

using namespace std;

#define CLASSNAME "UntitledWareOverlay"

HWND dxOverlay::hWindow, dxOverlay::thWindow = nullptr;

dxOverlay::dxOverlay(App* csgo) {
    thWindow = csgo->GetWindowHandle();
    CreateDXOverlay();
}

dxOverlay::~dxOverlay() {
    if ( iDirectD3D9X ) { iDirectD3D9X->Release(); }
    if ( iDirectD3D9XDevice ) { iDirectD3D9XDevice->Release(); }
    if ( hWindow ) { DestroyWindow(hWindow); }
}

void dxOverlay::CreateDXOverlay() {
    WNDCLASSEX ovrlWindowClass;
    ovrlWindowClass.cbSize = sizeof(ovrlWindowClass);
    ovrlWindowClass.style = CS_NOCLOSE | CS_HREDRAW | CS_VREDRAW;
    ovrlWindowClass.lpfnWndProc = WindowProc;//https://learn.microsoft.com/ru-ru/windows/win32/learnwin32/writing-the-window-procedure
    ovrlWindowClass.cbClsExtra = 0;
    ovrlWindowClass.cbWndExtra = 0;
    ovrlWindowClass.hInstance = NULL;
    ovrlWindowClass.hIcon = LoadIconA(NULL,IDI_SHIELD);
    ovrlWindowClass.hCursor = LoadCursorA(NULL, IDC_ARROW);
    ovrlWindowClass.hbrBackground = HBRUSH(RGB(0, 0, 0));
    ovrlWindowClass.lpszMenuName = "UntitledWareMenu";
    ovrlWindowClass.lpszClassName = CLASSNAME;
    ovrlWindowClass.hIconSm = NULL;

    if (RegisterClassExA(&ovrlWindowClass) == 0) {
        Output::print("Can't Register overlay class", false, "CreateDXOverlay");
        init = false;
    }

    RECTMY window = (RECTMY)GetWindowRectMY(thWindow);

    hWindow = CreateWindowExA(
            WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT,
            CLASSNAME,
            "UntitledWare Main",
            WS_POPUP | WS_VISIBLE,
            window.left,
            window.top,
            window.weight(),
            window.height(),
            NULL,
            NULL,
            NULL,
            NULL
    );
    if (!hWindow) { Output::print("Window has not created", false, "CreateDXOverlay"); init = false; }
    MARGINS margins(
            window.left,
            window.right,
            window.top,
            window.bottom
    );
    DwmExtendFrameIntoClientArea(hWindow, &margins);

    SetLayeredWindowAttributes(hWindow, RGB(0, 0, 0), 255, LWA_ALPHA);

    ShowWindow(hWindow, SW_SHOW);

    InitDirectX9();
}

void dxOverlay::InitDirectX9() {
    iDirectD3D9X = Direct3DCreate9(D3D_SDK_VERSION);
    if (!iDirectD3D9X) { Output::printWithErrorCode("Failed Direct3DCreate9", "InitDirectX9");return; }
    D3DPRESENT_PARAMETERS d3Params;

    ZeroMemory(&d3Params, sizeof(d3Params));
    RECTMY window = (RECTMY)GetWindowRectMY(thWindow);
    d3Params.Windowed = true;
    d3Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3Params.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3Params.BackBufferHeight = window.height();
    d3Params.BackBufferWidth = window.weight();
    d3Params.hDeviceWindow = hWindow;
    d3Params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;


    if ( iDirectD3D9X->CreateDevice(
                    D3DADAPTER_DEFAULT,
                    D3DDEVTYPE_HAL,
                    hWindow,
                    D3DCREATE_HARDWARE_VERTEXPROCESSING,
                    &d3Params,
                    &iDirectD3D9XDevice
            )!= D3D_OK) {
        Output::printWithErrorCode("Error in device","InitDirectX9");
        iDirectD3D9X->Release();
        init = false;
    }
}

LRESULT CALLBACK dxOverlay::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    RECTMY window = GetWindowRectMY(thWindow);
    SetWindowPos(hWindow,HWND_TOPMOST,window.left,window.top,window.weight(),window.height(),NULL);
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool dxOverlay::isInitilizate()   {   return init;   }
dxRender dxOverlay::CreateRender() {
    return dxRender(iDirectD3D9XDevice, hWindow, hWindow);
}

HWND dxOverlay::GetWindowHandle() {
    return hWindow;
}

dxOverlay::RECTMY dxOverlay::GetWindowRectMY(HWND hwnd) {
    RECTMY rect;
    GetWindowRect(hwnd,&rect);

    rect.top += 26;
    rect.bottom += 26;
    rect.left += 3;
    rect.right += 3;

    return rect;
}