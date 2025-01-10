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

void dxRender::drawLine(POINT* start, POINT* end, D3DCOLOR color) {
    dxLine->Draw( new D3DXVECTOR2 [2]{ D3DXVECTOR2(start->x, start->y) ,D3DXVECTOR2(end->x, end->y)},2,color);
}

void dxRender::drawText(POINT* pos, std::string text, D3DCOLOR color, int size) {
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

void dxRender::drawBox(RECT* rect, D3DCOLOR color,char * gFlags, vector<int> idTexture) {
    if(gFlags[0]==DB_OUTLINE||gFlags[1]==DB_OUTLINE) {
        const int _size = 5;
        D3DXVECTOR2 mergins[5]{
                D3DXVECTOR2(rect->left,rect->top),
                D3DXVECTOR2(rect->left,rect->bottom),
                D3DXVECTOR2(rect->right,rect->bottom),
                D3DXVECTOR2(rect->right,rect->top),
                D3DXVECTOR2(rect->left,rect->top)
        };
        dxLine->Draw(mergins,_size,color);
    }
    if ((gFlags[1]==DB_FILLED || gFlags[0]==DB_FILLED) && idTexture[0]!=-1) {
        dxSprite->Begin(0);
        for(int i : idTexture) {
            dxSprite->Draw(textures[i], NULL, NULL, new D3DXVECTOR3(rect->left,rect->top,0), color);
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

RECT dxRender::GetWindowPos(HWND handle) {
    RECT rect;
    GetWindowRect(handle, &rect);
    MapWindowPoints(HWND_DESKTOP,GetParent(handle), (LPPOINT)(&rect),2);

    return rect;
}

void dxRender::Button(RECT* rectButton, D3DCOLOR color, bool* varible) {
    drawBox(rectButton, color);
    POINT cursor;
    GetCursorPos(&cursor);
    RECT window = GetWindowPos(hWindow);

    RECT butonInWindows(        rectButton->left + window.left,
                                 rectButton->top + window.top,
                              rectButton->right + window.left,
                           rectButton->bottom + window.top
    );

    if  (   cursor.y < butonInWindows.bottom &&
            cursor.y > butonInWindows.top &&
            cursor.x > butonInWindows.left &&
            cursor.x<butonInWindows.right &&
            GetAsyncKeyState(VK_LBUTTON)
        )
    {
                    *varible = true;
    } else {
        *varible = false;
    }
}

void dxRender::DragMenu(RECT* menuRect) {
    static POINT cursor(0,0);
    RECT window = GetWindowPos(hWindow);
    RECT menuInWindow(
                    menuRect->left   + window.left,
                    menuRect->top    + window.top,
                   menuRect->right  + window.left,
                    menuRect->bottom + window.top - (((menuRect->bottom-menuRect->top)*88)/100)
    );
    //cout << "MenuInWindow: left"<<menuInWindow.left<<", right"<<menuInWindow.right<<", top"<<menuInWindow.top<<", bottom"<<menuInWindow.bottom<<"Cursor - > "<<cursor.y<<endl;

    if  (   cursor.y > menuInWindow.top &&
            cursor.y < menuInWindow.bottom &&
            cursor.x > menuInWindow.left &&
            cursor.x < menuInWindow.right &&
            GetAsyncKeyState(VK_LBUTTON)
        )
    {
        const float cof = .2f;
        float DELTA[2];
        POINT newCursorPos;
        GetCursorPos(&newCursorPos);

        DELTA[0] = (newCursorPos.x-cursor.x)*cof;
        DELTA[1] = (newCursorPos.y-cursor.y)*cof;

        //cout <<"DElta " << DELTA[0] << " "<<DELTA[1]<<endl;

        menuRect->left += DELTA[0];
        menuRect->right += DELTA[0];
        menuRect->top += DELTA[1];
        menuRect->bottom += DELTA[1];
    } else {
        //cout<<"non";
        GetCursorPos(&cursor);
    }
}