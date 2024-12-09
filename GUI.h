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
    float weight, height;
    bool exit;
    POINTS pos;

    HWND window;
    WNDCLASSEXA windowClass;

    PDIRECT3D9 p3D9;
    LPDIRECT3DDEVICE9 device;
    D3DPRESENT_PARAMETERS  presentParams;

    //long __stdcall WindowProcess(HWND window,UINT message,WPARAM wParams, LPARAM lParams);

    void WindowCreate(string, string);
    void Destroy();
    long __stdcall WindowProcess(HWND window,UINT message,WPARAM wParams, LPARAM lParams);
    bool CreateDevice();
    static void ResetDevice();
    void DestroyDevice();

    void CreateImGui();
    void DestroyImGui();
    void BeginRender();
    void EndRender();
    void Render();

    GUI(int,int);
};


#endif //UNTITLEDWARE_GUI_H