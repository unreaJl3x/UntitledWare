#ifndef UNTITLEDWARE_DXRENDER_H
#define UNTITLEDWARE_DXRENDER_H

#include "iostream"
#include "output.h"

#include <d3d9.h>
#include <d3dx9core.h>
#include <windows.h>
#include <vector>
#include <map>

using namespace std;
#define DB_OUTLINE 'o'
#define DB_FILLED 'f'

class dxRender {
private:
    std::map<int, IDirect3DTexture9*> textures;
    vector<int> keys;
    IDirect3DDevice9* device;
    ID3DXLine* dxLine;
    ID3DXFont* dxFont;
    ID3DXSprite* dxSprite;
    HWND hWindow;
    RECT GetWindowPos(HWND);

    HWND thWindow;
    static VOID WINAPI ColorFill (D3DXVECTOR4* pOut, const D3DXVECTOR2* pTexCoord,const D3DXVECTOR2* pTexelSize, LPVOID pData);

public:
    dxRender(IDirect3DDevice9*, HWND,HWND);
    ~dxRender();

    void beginRender();
    void endRender();

    void drawLine(POINT*, POINT*, D3DCOLOR);
    void drawBox(RECT*, D3DCOLOR,char* = new char[1]{DB_OUTLINE},vector<int> = *(new vector{-1}));
    bool addTexture(RECT* rect, int idTexture);
    void drawText(POINT*, std::string, D3DCOLOR, int);

    void DragMenu(RECT*);
    void Button(RECT*, D3DCOLOR, bool*);

    static vector<int> GetARGBCode(D3DCOLOR);

    static struct COLOR {
        static const inline D3DCOLOR RED =          D3DCOLOR_ARGB(255, 255, 0  , 0  );
        static const inline D3DCOLOR GREEN =        D3DCOLOR_ARGB(255, 0  , 255, 0  );
        static const inline D3DCOLOR YELLOW =       D3DCOLOR_ARGB(255, 238, 255, 0  );
        static const inline D3DCOLOR BLUE =         D3DCOLOR_ARGB(255, 0  , 0  , 255);
        static const inline D3DCOLOR WHITE =        D3DCOLOR_ARGB(255, 255, 255, 255);
        static const inline D3DCOLOR BLACK =        D3DCOLOR_ARGB(255, 0  , 0  , 0  );
        static const inline D3DCOLOR WHITEBLUE =    D3DCOLOR_ARGB(255, 0  , 183, 255);
        static const inline D3DCOLOR PURPLE =       D3DCOLOR_ARGB(255, 0  , 183, 255);
        static const inline D3DCOLOR ORANGE =       D3DCOLOR_ARGB(255, 255, 132, 0  );
        static const inline D3DCOLOR PINK =         D3DCOLOR_ARGB(255, 255, 148, 216);
        static const inline D3DCOLOR GRAY =         D3DCOLOR_ARGB(255, 125, 125, 125);
        static const inline D3DCOLOR BLACKGRAY =    D3DCOLOR_ARGB(255, 41 , 41 , 41 );
        static const inline D3DCOLOR VERYBLACKGRAY= D3DCOLOR_ARGB(255, 23 , 23 , 23 );
        static const inline D3DCOLOR BLACKBLUE =    D3DCOLOR_ARGB(255, 2  , 29 , 77 );
        static D3DCOLOR Rainbow(D3DCOLOR lastColor) {
            vector<int> color = GetARGBCode(lastColor);
            if (color[1] == 255) {
                if (color[2]==255) {
                    color[1]--;
                }
                else if (color[3]!=0) {
                    color[3]--;
                }
                else {
                    color[2]++;
                }
            }
            else if (color[2] == 255) {
                if (color[1]!=0) {
                    color[1]--;
                } else {
                    if (color[3]==255) {
                        color[2]--;
                    } else {
                        color[3]++;
                    }
                }
            }
            else if (color[3] == 255){
                if (color[2]!=0) {
                    color[2]--;
                } else {
                    if (color[1]==255) {
                        color[3]--;
                    } else {
                        color[1]++;
                    }
                }
            } else {Output::print("Error",false,"Rainbow");}

            return D3DCOLOR_ARGB(color[0],color[1],color[2],color[3]);
        }
    };
};

#endif //UNTITLEDWARE_DXRENDER_H