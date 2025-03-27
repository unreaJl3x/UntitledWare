#ifndef UNTITLEDWARE_DXRENDER_H
#define UNTITLEDWARE_DXRENDER_H

#include "iostream"
#include "output.h"

#include <d3d9.h>
#include <d3dx9core.h>
#include <windows.h>
#include <vector>
#include <thread>
#include <chrono>
#include <map>

using namespace std;
#define DB_OUTLINE 'o'
#define DB_FILLED 'f'

class dxRender {
private:
    std::map<int, IDirect3DTexture9*> textures;
    IDirect3DDevice9* device;
    ID3DXSprite* dxSprite;
    ID3DXLine* dxLine;
    ID3DXFont* dxFont;
    vector<int> keys;
    HWND thWindow;
    HWND hWindow;

public:
    dxRender            ( IDirect3DDevice9*, HWND,HWND );
    ~dxRender           (   );

    void beginRender    (   );
    void endRender      (   );

    void drawLine       ( POINT*, POINT*, D3DCOLOR );
    void drawBox        ( RECT* rect, D3DCOLOR color, vector<char>* params = new vector{DB_OUTLINE}, vector<int>* texturesid= new vector{-1});
    int  addTexture     ( RECT* rect);
    int addTextureFromImage (RECT*, string);
    void drawText       ( POINT*, std::string, D3DCOLOR, int);

    HWND GetHW();
    HWND GetTHW();

    static void CircleDrag(RECT* r,HWND hw,HWND thw,LONG s , float speeMod, bool verticalLock, bool horizontalLock , POINT *limits, RECT c ) {
        while (true) {
            DragRect(r, hw, thw, s, speeMod,verticalLock,horizontalLock,limits,c);
            // cout << "1"<<endl;
        }
    }
    static POINT DragRect ( RECT*,HWND hw,HWND thw,LONG =0, float = 1.f, bool verticalLock = false, bool horizontalLock = false, POINT *limits = new POINT[2]{(INT_MAX, INT_MAX),(INT_MAX, INT_MAX)}, RECT = RECT(0,0,0,0));
    void Button         ( RECT* , bool*);

    static vector<int> GetARGBCode  ( D3DCOLOR );
    static RECT* GetWindowPos       ( HWND);
    static string ChangingString    ( string, int );

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
    static RECT* Transform  (RECT* menu, RECT* obj) { return new RECT(menu->left+obj->left,menu->top+obj->top,menu->left+obj->right,menu->top+obj->bottom); }
    static LONG width       (       RECT* rect    ) { return rect->right-rect->left; }
    static LONG height      (       RECT* rect    ) { return rect->bottom-rect->top; }

private:
    static VOID WINAPI ColorFill (D3DXVECTOR4* pOut, const D3DXVECTOR2* pTexCoord,const D3DXVECTOR2* pTexelSize, LPVOID pData);
public:
    static bool WGetKeyState(int key) {
        this_thread::sleep_for(chrono::milliseconds(10));
        return (GetKeyState(key)==-127||GetKeyState(key)==-128 );
    }
};

#endif