#include "dxRender.h"
#include <d3dx9tex.h>
#include <string>
#include <mutex>

HWND dxRender::GetHW() {
    return hWindow;
}
HWND dxRender::GetTHW() {
    return thWindow;
}

dxRender::dxRender(IDirect3DDevice9 *device, HWND handleWindow, HWND targetHandleWindow) {
    if (!device) {
        Output::print("Invalid device", false, "dxRender");
        return;
    }
    this->device = device;
    this->hWindow = handleWindow;
    this->thWindow = targetHandleWindow;
    if (D3DXCreateLine(device, &dxLine) != D3D_OK) {
        Output::print("Failed crate dxLine", false, "dxRender");
    }
    D3DXCreateFontA(device,
                    dxRender::height(dxRender::GetWindowPos(hWindow))/40,
                    dxRender::width(dxRender::GetWindowPos(hWindow))/80,
                    FW_HEAVY,
                    1,
                    false,
                    DEFAULT_CHARSET,
                    OUT_TT_ONLY_PRECIS,
                    ANTIALIASED_QUALITY,
                    DEFAULT_PITCH | FF_DONTCARE,
                    "Tahoma",
                    &dxFont
    );
    D3DXCreateSprite(device,&dxSprite);
}

dxRender::~dxRender() {
    if (device)     { device->Release(); }
    if (dxLine)     { dxLine->Release(); }
    if (dxSprite)   { dxLine->Release(); }
    if (dxFont)     { dxLine->Release(); }
}

void dxRender::beginRender() {
    if (device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1, 0) != D3D_OK) {
        Output::print("Failed clear scene", false, "beginRender");
    }
    device->BeginScene();
}

void dxRender::endRender() {
    device->EndScene();
    device->Present(NULL, NULL, NULL, NULL);
}

void dxRender::drawLine(POINT* start, POINT* end, D3DCOLOR color) {
    dxLine->Draw( new D3DXVECTOR2 [2]{ D3DXVECTOR2(start->x, start->y) ,D3DXVECTOR2(end->x, end->y)},2,color);
}

void dxRender::drawText(POINT* pos, std::string text, D3DCOLOR color, int size) {
    //cout << text.c_str()<<endl;
    dxFont->DrawTextA(NULL, text.c_str(), text.length(), new RECT(pos->x,pos->y,pos->x*size,pos->y*size), DT_LEFT|DT_NOCLIP, color);
}

VOID WINAPI dxRender::ColorFill(D3DXVECTOR4* pOut, const D3DXVECTOR2* pTexCoord, const D3DXVECTOR2* pTexelSize, LPVOID pData)
{
    *pOut = D3DXVECTOR4(255.f / 255.f, 255.f / 255.f, 255.f / 255.f, 0.9f);
}

vector<int> dxRender::GetARGBCode(D3DCOLOR input) {
    vector<int> COLOR_ARGB;
    const int mod[4] {16777216,65536,256,1};
    unsigned long colorCode = input;

    int colorCount = 0;
    for (int m : mod) {
        while (colorCode>=m) {
            colorCode-=m;
            colorCount++;
        }
        COLOR_ARGB.push_back(colorCount);
        colorCount = 0;
    }
    return COLOR_ARGB;
}

void dxRender::drawBox(RECT* rect, D3DCOLOR color, vector<char>* gFlags, vector<int>* idTexture) {
    for (char mode : *gFlags) {
        switch(mode) {
            case DB_OUTLINE: {
                const int _size = 5;
                D3DXVECTOR2 mergins[5]{
                    D3DXVECTOR2(rect->left,rect->top),
                    D3DXVECTOR2(rect->left,rect->bottom),
                    D3DXVECTOR2(rect->right,rect->bottom),
                    D3DXVECTOR2(rect->right,rect->top),
                    D3DXVECTOR2(rect->left,rect->top)
                    };
                dxLine->Draw(mergins, _size, color);
                break;
            }

            case DB_FILLED: {
                if (idTexture[0][0] == -1) {break;}
                dxSprite->Begin(D3DXSPRITE_ALPHABLEND);
                for(int i : *idTexture) {
                    dxSprite->Draw(textures[i], NULL, NULL, new D3DXVECTOR3(rect->left,rect->top,0), color);
                }
                dxSprite->End();
                break;
            }
        }
    }
}

/// \return
int dxRender::addTexture(RECT* rect) {
    int key;
    if (keys.size() !=0) {
        key = keys.back() + 1;
    } else {key = 0;}

    keys.push_back(key);
    bool createTexture = device->CreateTexture(rect->right-rect->left,
                          rect->bottom-rect->top,
                          0,
                          0,
                          D3DFMT_A8R8G8B8 ,
                          D3DPOOL_DEFAULT,
                          &textures[key],
                          NULL
    ) == D3D_OK;

    D3DXFillTexture(textures[key], ColorFill, NULL);
    return createTexture ? key : -1;
}

RECT* dxRender::GetWindowPos(HWND handle) {
    RECT rectt;
    GetWindowRect(handle, &rectt);
    MapWindowPoints(HWND_DESKTOP,GetParent(handle), (LPPOINT)(&rectt),2);

    return &rectt;
}

void dxRender::Button(RECT* rectButton, bool* var) {
    RECT window = *dxRender::GetWindowPos(hWindow);
    RECT menu = *rectButton;
    POINT cursorePos;
    GetCursorPos(&cursorePos);
    static bool cannable;

    if (
        cursorePos.x > menu.left + window.left &&
        cursorePos.x < menu.right + window.left &&
        cursorePos.y > menu.top + window.top &&
        cursorePos.y < menu.bottom + window.top
    )
    {
        if (WGetKeyState(VK_LBUTTON) && cannable) {
            cannable = false;
            *var = !(*var);
            this_thread::sleep_for(chrono::milliseconds(100));
            return;
        }
    } else {
        cannable = true;
    }

    return;
}

mutex _m;
POINT dxRender::DragRect(RECT* objRect, HWND hWindow, HWND thWindow, long prochent, float speed,  bool verticalLock, bool horizontalLock, POINT* limits, RECT dRect) {
    _m.lock();
    static POINT cursor(0,0);
    RECT window = *GetWindowPos(hWindow);
    RECT menuInWindow(
                    objRect->left   + window.left + dRect.left,
                    objRect->top    + window.top+ dRect.top,
                   objRect->right  + window.left+ dRect.left,
                    objRect->bottom + window.top+ dRect.bottom - (((objRect->bottom-objRect->top)*prochent)/100)
    );
    /*cout << "MENU: " << objRect->left << " " << objRect->right << " " << objRect->top << " " << objRect->bottom
<< "menuInWindow: " << menuInWindow.left << " " << menuInWindow.right << " " << menuInWindow.top << " " << menuInWindow.bottom <<  "\r";*/

    if  (   cursor.y > menuInWindow.top &&
            cursor.y < menuInWindow.bottom &&
            cursor.x > menuInWindow.left &&
            cursor.x < menuInWindow.right &&
            WGetKeyState(VK_LBUTTON)
        )
    {
        POINT newCursorPos;
        GetCursorPos(&newCursorPos);

        const float cof = 1.2f*speed;
        POINT DELTA(( newCursorPos.x - cursor.x ) * cof, ( newCursorPos.y - cursor.y ) * cof);

        int victimW[2](dxRender::width(dxRender::GetWindowPos(thWindow))-dxRender::width(dxRender::GetWindowPos(thWindow))*2/100, dxRender::height(dxRender::GetWindowPos(thWindow))-dxRender::height(dxRender::GetWindowPos(thWindow))*7/100);

        if ((!(objRect->left + DELTA.x < 0 || objRect->right + DELTA.x> victimW[0])) && !horizontalLock) {
            //
            //cout <<limits[0].x<<endl;
            if ((objRect->left+DELTA.x > limits[0].x && objRect->left+DELTA.x < limits[1].x)&& limits[0].x!=INT_MAX) {
                objRect->left += DELTA.x;  objRect->right += DELTA.x;
            }
            else if (limits[0].x == INT_MAX) {
                objRect->left += DELTA.x;  objRect->right += DELTA.x;
            }

        }

        if ((!(objRect->top + DELTA.y < 0 || objRect->bottom + DELTA.y > victimW[1])) && !verticalLock ) {  objRect->top += DELTA.y;  objRect->bottom += DELTA.y; }
        else {}

        GetCursorPos(&cursor);
        _m.unlock();
        return DELTA;
    } else {
        GetCursorPos(&cursor);
        //cout << "CURSORE: "<<cursor.x<< " , "<<cursor.y<<endl;
    }
    _m.unlock();
    return POINT(0,0);
}

string dxRender::ChangingString(string _text, int speed) {
    static string text = _text;
    string changedString = "";
    static int num = 0;
    static int time, time2 = 1;
    time++;
    if (time%speed==0) {
        if (num >= text.size()) {
            if (time2 % (speed+(speed*40/100)) == 0) {
                num = 0;
                time2=1;
            } else { time2++; }
        }
        else {
            num++;
        }
    }
    for (int i = 0; i < num; i++) {
        changedString += text[i];
    }

    return changedString;
}

int dxRender::addTextureFromImage(RECT* rect, string path) {
    int key;
    if (keys.size() !=0) {
        key = keys.back() + 1;
    } else { key = 0; }

    keys.push_back(key);
    /*bool createTexture = device->CreateTexture(rect->right-rect->left,
                         rect->bottom-rect->top,
                         0,
                         0,
                         D3DFMT_A8R8G8B8 ,
                         D3DPOOL_DEFAULT,
                         &textures[key],
                         NULL
   ) == D3D_OK;*/
    bool createTexture = D3DXCreateTextureFromFileEx(device, path.c_str(), rect->right-rect->left,rect->bottom-rect->top, D3DX_DEFAULT,
                          0,
                          D3DFMT_UNKNOWN ,
                          D3DPOOL_MANAGED, D3DX_DEFAULT,D3DX_DEFAULT,0,NULL,NULL, &textures[key]
        ) == D3D_OK;

    //D3DXFillTexture(textures[key], ColorFill, NULL);
    //D3DXSaveTextureToFileA("1.png",D3DXIFF_PNG,textures[key],NULL);
    //cout << createTexture <<endl;
    return key;
}
