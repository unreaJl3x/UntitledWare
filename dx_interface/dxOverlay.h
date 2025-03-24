#ifndef UNTITLEDWARE_DXOVERLAY_H
#define UNTITLEDWARE_DXOVERLAY_H

#include <d3d9.h>
#include <d3dx9.h>

#include "App.h"
#include "dxRender.h"
#include "WRECT.h"

class dxOverlay {
private:
    static struct RECTMY : RECT {
        int weight() {return right-left;}
        int height() {return bottom-top;}
    };

    IDirect3D9* iDirectD3D9X ;
    IDirect3DDevice9* iDirectD3D9XDevice ;

    static HWND hWindow, thWindow;

    bool init = true;

    void CreateDXOverlay();
    void InitDirectX9();

    static RECTMY GetWindowRectMY(HWND);

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    bool isInitilizate();

    dxRender CreateRender();

    HWND GetWindowHandle();
    HWND GetVictimWindowHandle();

    dxOverlay(App*);
    ~dxOverlay();
};


#endif //UNTITLEDWARE_DXOVERLAY_H