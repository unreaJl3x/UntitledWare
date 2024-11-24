#ifndef UNTITLEDWARE_GUI_H
#define UNTITLEDWARE_GUI_H

#include <d3d9.h>
#include <iostream>
#include <windows.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
using namespace std;

class GUI {
public:
    static int weight, height;
    static bool exit;
    static  POINTS pos;

    static HWND window;
    static WNDCLASSEXA windowClass;

    static PDIRECT3D9 p3D9;
    static LPDIRECT3DDEVICE9 device;
    static D3DPRESENT_PARAMETERS  presentParams;

    //long __stdcall WindowProcess(HWND window,UINT message,WPARAM wParams, LPARAM lParams);

    void WindowCreate(string, string);
    void Destroy();

    bool CreateDevice();
    static void ResetDevice();
    void DestroyDevice();

    void CreateImGui();
    void DestroyImGui();
};


#endif //UNTITLEDWARE_GUI_H