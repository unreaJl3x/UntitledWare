#include "dxRender.h"
#include <d3dx9tex.h>

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
                    15,
                    10,
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

void dxRender::drawLine(POINT start, POINT end, D3DCOLOR color) {
    D3DXVECTOR2 vector[2] = {D3DXVECTOR2(start.x, start.y), D3DXVECTOR2(end.x, end.y)};
    dxLine->Draw(vector, 2, color);
}

void dxRender::drawText(POINT pos, std::string text, D3DCOLOR color, int size) {
    RECT r(pos.x,pos.y,pos.x*size,pos.y*size);
    dxFont->DrawTextA(NULL, text.c_str(), text.length(), &r, DT_LEFT|DT_NOCLIP, color);
}




VOID WINAPI dxRender::ColorFill (D3DXVECTOR4* pOut, const D3DXVECTOR2* pTexCoord, const D3DXVECTOR2* pTexelSize, LPVOID pData)
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

void dxRender::DragMenu(RECT* menu) {
    static POINT cursorePos = {10000,10000};
    RECT targetWindow;
    GetWindowRect(thWindow,&targetWindow);
    int dragPlace =((((targetWindow.bottom)+menu->bottom) - (targetWindow.top)+menu->top)* 30 )/100;

    if (GetAsyncKeyState(VK_LBUTTON) && cursorePos.y < dragPlace) {
        POINT newCursore;
        GetCursorPos(&newCursore);
        const static float coof = 1.2f;
        POINT delta {(newCursore.x-cursorePos.x),(newCursore.y-cursorePos.y)};
        if (delta.x!=0) {
            //cout <<"Delta x:" << delta.x<<endl;
            menu->left += delta.x*coof;
            menu->right = delta.x*coof;
        }
        if (delta.y!=0) {
            //cout <<"Delta y:" << delta.y<<endl;
            menu->top += delta.y*coof;
            menu->bottom += delta.y*coof;
        }
        GetCursorPos(&cursorePos);
    } else {
        GetCursorPos(&cursorePos);
    }
}

void dxRender::drawBox(RECT* rect, D3DCOLOR* color,char * gFlags, vector<int> idTexture) {
    if(gFlags[0]==DB_OUTLINE||gFlags[1]==DB_OUTLINE) {
        const int _size = 5;
        D3DXVECTOR2 mergins[5]{
                D3DXVECTOR2(rect->left,rect->top),
                D3DXVECTOR2(rect->left,rect->bottom),
                D3DXVECTOR2(rect->right,rect->bottom),
                D3DXVECTOR2(rect->right,rect->top),
                D3DXVECTOR2(rect->left,rect->top)
        };
        dxLine->Draw(mergins,_size,*color);
    }
    if ((gFlags[1]==DB_FILLED || gFlags[0]==DB_FILLED) && idTexture[0]!=-1) {
        dxSprite->Begin(0);
        for(int i : idTexture) {
            cout<<i<<endl;
            dxSprite->Draw(textures[i], NULL, NULL, new D3DXVECTOR3(rect->left,rect->top,0), *color);
        }
        dxSprite->End();
    }
}

bool dxRender::addTexture(RECT* rect, int idTexture) {
    bool newKey = true;
    for(int i : keys) {
        if(i==idTexture) newKey = false;
    }
    if(newKey) {
        cout<<"vrea"<<endl;
        keys.push_back(idTexture);
        device->CreateTexture(rect->right-rect->left,
                              rect->bottom-rect->top,
                              0,
                              0,
                              D3DFMT_A8R8G8B8 ,
                              D3DPOOL_DEFAULT,
                              &textures[idTexture],
                              NULL
        );
        D3DXFillTexture(textures[idTexture],ColorFill,NULL);
        return true;
    }
    return false;
}