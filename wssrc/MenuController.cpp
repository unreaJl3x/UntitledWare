#include "MenuController.h"

MenuController::MenuController(dxOverlay* o, dxRender* re, bool* menuBool, D3DCOLOR* color) {
    over = o;
    rend = re;
    CreateParent("MAIN", menuBool);
    CreatePlace("Main", color, &GetRect()->left, &GetRect()->top,&GetRect()->right,&GetRect()->bottom,"MAIN", new char[1]{DB_FILLED});
}

void MenuController::SetRect(LONG x, LONG y, LONG w, LONG h) {
    window.left = x;
    window.top = y;
    window.right = w;
    window.bottom = h;
}
RECT* MenuController::GetRect() { return &window; }

bool MenuController::CreatePlace(string indef, D3DCOLOR* color, LONG* rX, LONG* rY, LONG* rW, LONG* rH, string parent , char* params) {
    bool newKey = true;
    if (placeKeys.size() != 0) {
        for(string k : placeKeys) { if ( k == indef ) { newKey = false; } }
    }
    if (newKey) {
        placeKeys.push_back(indef);
    }

    PlaceDate date;
    date.rectX = rX;
    date.rectY = rY;
    date.rectW = rW;
    date.rectH = rH;
    date.color = color;
    date.textureId = rend->addTexture(new RECT(*rX,*rY,*rW,*rH));
    date.parent = parent;
    date.param = params;

    places[indef] = date;

    return true;
}

void MenuController::Draw() {
    for(string pdKey : placeKeys) {
        if(*parents[places[pdKey].parent]) {
            RECT r(*places[pdKey].rectX,*places[pdKey].rectY,*places[pdKey].rectW,*places[pdKey].rectH);
            rend->drawBox(&r, *places[pdKey].color, places[pdKey].param,
                          new vector<int>{places[pdKey].textureId});
            for(string fdKey : fontKeys) {
                if (fonts[fdKey].parent == places[pdKey].parent) {
                    rend->drawText(new POINT((*fonts[fdKey].rectX),(*fonts[fdKey].rectY)), "Untitled.ware", *fonts[fdKey].color, fonts[fdKey].size);
                }
            }
        }
    }
    rend->DragMenu(&window);
}

bool MenuController::CreateText(string indef, string text, D3DCOLOR* color, int size, string parent) {
    bool newKey = true;
    if (fontKeys.size() != 0) {
        for (string key : fontKeys) {
            if (key==indef) { newKey=false; }
        }
    }
    if (newKey) {
        fontKeys.push_back(indef);
    }
    FontDate fd;
    fd.size = size;
    fd.color = color;
    fd.rectX = posX;
    fd.rectY = posY;
    fd.rectW = 0;
    fd.rectH = 0;
    fd.text = text;
    fd.parent = parent;

    fonts[indef] = fd;

    return true;
}

bool MenuController::CreateParent(string parent, bool* boolen) {
    if (parentKeys.size() != 0) {
        for (string key : parentKeys) {
            return false;
        }
    }

    parents[parent] = boolen;
    parentKeys.push_back(parent);

    return true;
}