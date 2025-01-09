#include "dxRender.h"
#include "wssrc/output.h"
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
}

dxRender::~dxRender() {
    if (device) { device->Release(); }
    if (dxLine) { dxLine->Release(); }
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

void dxRender::drawText(dxRender::POINT pos, std::string text, D3DCOLOR color, int size) {
    RECT r(pos.x,pos.y,pos.x*size,pos.y*size);
    dxFont->DrawTextA(NULL, text.c_str(), text.length(), &r, DT_LEFT|DT_NOCLIP, color);
}

void dxRender::drawBox(RECT rect, D3DCOLOR color, bool filled) {
    const int vertexCount = 5;
    D3DXVECTOR2 vector[vertexCount] = {
            D3DXVECTOR2(rect.left,rect.top),
            D3DXVECTOR2(rect.left,rect.bottom),
            D3DXVECTOR2(rect.right,rect.bottom),
            D3DXVECTOR2(rect.right,rect.top),
            D3DXVECTOR2(rect.left,rect.top)
    };
    dxLine->Draw(vector, vertexCount, color);

    if (!filled) {return;}

    ID3DXSprite* dxSprite;
    D3DXCreateSprite(device,&dxSprite);

    IDirect3DTexture9* texture;
    device->CreateTexture(rect.right-rect.left,
                          rect.bottom-rect.top,
                          1,
                          0,
                          D3DFMT_A8R8G8B8 ,
                          D3DPOOL_DEFAULT,
                          &texture,
                          NULL
  );

    D3DXFillTexture (texture, ColorFill, (LPVOID)color);
    D3DXSaveTextureToFile("texture.png", D3DXIFF_PNG, texture, NULL);
    dxSprite->Begin(0);
    D3DXVECTOR3 v(rect.left,rect.top,0);
    dxSprite->Draw(texture,NULL,NULL,&v,color);
    dxSprite->End();
}

VOID WINAPI dxRender::ColorFill (D3DXVECTOR4* pOut, const D3DXVECTOR2* pTexCoord, const D3DXVECTOR2* pTexelSize, LPVOID pData)
{
    *pOut = D3DXVECTOR4(255.f / 255.f, 255.f / 255.f, 255.f / 255.f, 0.9f);
}