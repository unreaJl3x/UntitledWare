#ifndef UNTITLEDWARE_DXRENDER_H
#define UNTITLEDWARE_DXRENDER_H

#include "iostream"
#include <d3d9.h>
#include <d3dx9core.h>
#include <windows.h>

class dxRender {
private:
    struct POINT {
        int x,y;
    };
    IDirect3DDevice9* device;
    ID3DXLine* dxLine;
    ID3DXFont* dxFont;

    HWND thWindow;
    HWND hWindow;

public:
    dxRender(IDirect3DDevice9*, HWND,HWND);
    ~dxRender();

    void drawLine(POINT, POINT, D3DCOLOR);
    void drawText(POINT, std::string*, D3DCOLOR, int);

    void beginRender();
    void endRender();

    static struct COLOR {
        static const inline D3DCOLOR RED =       D3DCOLOR_ARGB(255, 255, 0  , 0  );
        static const inline D3DCOLOR GREEN =     D3DCOLOR_ARGB(255, 0  , 255, 0  );
        static const inline D3DCOLOR YELLOW =    D3DCOLOR_ARGB(255, 238, 255, 0  );
        static const inline D3DCOLOR BLUE =      D3DCOLOR_ARGB(255, 0  , 0  , 255);
        static const inline D3DCOLOR WHITE =     D3DCOLOR_ARGB(255, 255, 255, 255);
        static const inline D3DCOLOR BLACK =     D3DCOLOR_ARGB(255, 0  , 0  , 0  );
        static const inline D3DCOLOR WHITEBLUE = D3DCOLOR_ARGB(255, 0  , 183, 255);
        static const inline D3DCOLOR PURPLE =    D3DCOLOR_ARGB(255, 0  , 183, 255);
        static const inline D3DCOLOR ORANGE =    D3DCOLOR_ARGB(255, 255, 132, 0  );
        static const inline D3DCOLOR PINK =      D3DCOLOR_ARGB(255, 255, 148, 216);
    };
};


#endif //UNTITLEDWARE_DXRENDER_H
