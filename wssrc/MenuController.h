#ifndef UNTITLEDWARE_MENUCONTROLLER_H
#define UNTITLEDWARE_MENUCONTROLLER_H

#include <iostream>
#include <map>
#include <vector>
#include "dx_interface/dxOverlay.h"
#include "dx_interface/dxRender.h"
using namespace std;

#define W_WIDTH_DEFAULT  350
#define W_HEIGHT_DEFAULT 300
#define MAIN_PARENT "MAIN"
class MenuController {
private:
    static inline RECT window = RECT(0, 0, W_WIDTH_DEFAULT, W_HEIGHT_DEFAULT);
    dxOverlay* over;
    dxRender* rend;
    struct Date {
    public:
        D3DCOLOR* color;
        LONG* rectX;
        LONG* rectY;
        LONG* rectW;
        LONG* rectH;
        string parent;
    };
    struct PlaceDate : Date{
        int textureId;
        char* param;
    };
    struct FontDate : Date {
        int size;
        string text;
    };
    map<string, PlaceDate>places;
    vector<string> placeKeys;

    map<string, FontDate> fonts;
    vector<string> fontKeys;

    map<string, bool*> parents;
    vector<string> parentKeys;

    map<string,D3DCOLOR> colors;
    vector<string> colorKeys;
public:
    void SetRect(LONG,LONG,LONG,LONG);
    static RECT* GetRect();

    bool CreateParent(string, bool*);

    bool AddColor(string, D3DCOLOR);
    void GetColor(string);

    bool CreatePlace(string, D3DCOLOR*, LONG*,LONG*,LONG*,LONG*, string, char*);
    bool CreateText(string, string, D3DCOLOR*, LONG*, LONG*, int, string);
    void CreateButton();
    void CreateLine();
    void CreateSlider();

    MenuController(dxOverlay*, dxRender*, bool*, D3DCOLOR*);
    void Draw();
};


#endif //UNTITLEDWARE_MENUCONTROLLER_H
