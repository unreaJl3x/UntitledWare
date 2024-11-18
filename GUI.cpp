#include "GUI.h"

extern IMGUI_IMPL_API LRESULT ImGuiWin32WndHandle(HWND window,UINT message,WPARAM wParams,LPARAM lParams);

long __stdcall WindowProcess(HWND window,UINT message,WPARAM wParams, LPARAM lParams)
{
    if (ImGuiWin32WndHandle(window, message, wParams, lParams)) return true;
    switch(message) {
        case WM_SIZE: {
            if (GUI::device && wParams != SIZE_MINIMIZED) {
                GUI::presentParams.BackBufferWidth = LOWORD(lParams);
                GUI::presentParams.BackBufferHeight = HIWORD(lParams);
                GUI::ResetDevice();
            }
        }return 0;
        case WM_SYSCOMMAND: {
            if ((wParams&0xfff0)==SC_KEYMENU) return 0;

        }break;
        case WM_DESTROY: {
            PostQuitMessage(0);
        } return 0;
        case WM_LBUTTONDOWN: {
            GUI::pos = MAKEPOINTS(lParams);
        }return 0;
        case WM_MOUSEMOVE: {
            if (wParams == MK_LBUTTON) {
                const tagPOINTS points = MAKEPOINTS(lParams);
                RECT rect = ::RECT{};
                GetWindowRect(window,&rect);
                rect.left += points.x - GUI::pos.x;
                rect.top += points.y - GUI::pos.y;
                if (GUI::pos.x >= 0 && GUI::pos.x <= GUI::weight && GUI::pos.y >= 0 && GUI::pos.y <= 19) {
                    SetWindowPos(window,HWND_TOPMOST,rect.left,rect.top,0,0,SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOZORDER);
                }
            }
        }
    }
    return DefWindowProcW(window,message,wParams,lParams);
}

void GUI::WindowCreate(string windowName, string className) {
    windowClass.cbSize = sizeof(WNDCLASSEXA );
    windowClass.style = CS_CLASSDC;
    windowClass.lpfnWndProc = WindowProcess;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = GetModuleHandleA(0);
    windowClass.hIcon = 0;
    windowClass.hCursor = 0;
    windowClass.hbrBackground = 0;
    windowClass.lpszMenuName = 0;
    windowClass.lpszClassName = className.c_str();
    windowClass.hIconSm = 0;

    RegisterClassExA(&windowClass);

    window = CreateWindowA(className.c_str(), windowName.c_str(), WS_POPUP, 100,100,weight,height,0,0,windowClass.hInstance,0);
    ShowWindow(window,SW_SHOWDEFAULT);
    UpdateWindow(window);
}

void GUI::Destroy() {
    DestroyWindow(window);
    UnregisterClass(windowClass.lpszClassName,windowClass.hInstance);
}

bool GUI::CreateDevice() {
    d3d
}