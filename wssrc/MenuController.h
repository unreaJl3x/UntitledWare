#ifndef UNTITLEDWARE_MENUCONTROLLER_H
#define UNTITLEDWARE_MENUCONTROLLER_H

#include <iostream>

#include "dx_interface/dxOverlay.h"
#include "dx_interface/dxRender.h"
#include "ConfController.h"
#include "map_and_keys.h"

#define DEFAULT_WINDOWRECTT_W 325
#define DEFAULT_WINDOWRECTT_H 200
#define DEFAULT_WINDOWPARENT "MAIN_MENU"
#define MAIN_WINDOW_NAME "Main"
#define DEFAULT_TITLELABEL_ID "Main"
#define DEFAULT_TITLEVALUE "Untitled.ware"
#define DEFAULT_WINDOWCOLOR_BACKGROUND "BACKGROUND"

class MenuController {

private:
    static inline RECT window = RECT(0, 0, DEFAULT_WINDOWRECTT_W, DEFAULT_WINDOWRECTT_H);
    ConfController* cfc;
    dxOverlay* over;
    dxRender* rend;

public:
    bool AddParent          ( string key, bool* value );
    bool RemoveParent       ( string key              );

    bool AddColor           ( string key, D3DCOLOR value );
    bool RemoveColor        ( string key                 );
    bool SetColor           ( string key, D3DCOLOR value );
    D3DCOLOR* GetColor      ( string key                 );

    bool AddLabel           ( string, string* );
    string GetLable         ( string );
    bool RemoveLabel        ( string               );
    bool SetLabel           ( string, string* );

    bool CreatePlace        ( string name, string parent, RECT* pPos, string color, vector<char>* pParams = new vector<char>{DB_OUTLINE});
    bool RemovePlace        ( string key);

    bool CreateText         ( string name, string parent, string text, string color, RECT* pos, int size );
    bool RemoveText         ( string key );
    
    bool CreateButton       ( string nameButton, string parent, RECT* pos, bool* varible, string colorName, vector<char>* pParams = new vector<char>{ DB_OUTLINE }, string labelOnButton = "", int size = 0 );
    bool RemoveButton       ( string key );

    bool RemoveLine         ( string key );

    bool CreateLine         ( string nameLine, string parent, RECT* pos, string colorName );
    bool CreateCheckBox     ( string chboxName, string parent,  string colorName, RECT* rect, bool* varible );
    bool RemoveCheckBox     (   );

    bool CreateKeyBind      ( string, string, RECT*, string, string, int, string );
    bool RemoveKeyBind      ( string);

    bool CreateSlider       ( string sliderName, string parent, RECT* pRect, string bgColor, string slideColor, int* varible, int max, int min);
    bool RemoveSlider       ( string);

    bool CreateColorPicker  (   );
    bool RemoveColorPicker  (   );

    bool CreateDragBow      (   );
    bool RemoveDragBox      (   );

    bool CreateInputPlace   (   );
    bool RemoveInputPlace   (  string );

    void      SetRect   (LONG,LONG,LONG,LONG);
    static RECT* GetRect();

    void Draw();

    MenuController(dxOverlay*, dxRender*, bool*, D3DCOLOR, ConfController*);

private: // STRUCTS
    struct WRECT : RECT {
        void operator+=(RECT* r) {
            this->left += r->left;
            this->top += r->top;
            this->bottom += r->top;
            this->right += r->left;
        }
        void operator+=(RECT r) {
            this->left += r.left;
            this->top += r.top;
            this->bottom += r.top;
            this->right += r.left;
        }
        void operator*=(RECT* r) {
            this->left += r->left;
            this->top += r->top;
            this->bottom += r->bottom;
            this->right += r->right;
        }
        void operator=(RECT* r) {
            this->left = r->left;
            this->top = r->top;
            this->bottom = r->bottom;
            this->right = r->right;
        }
    };
    struct Date {
        string colorKey;
        RECT* rect;
        string parent;
    };
    struct DatePlaces : Date {
        vector<char>* pParams;
        int textureId;
        DatePlaces() : Date() {}
    };
    struct DateText : Date {
        string labelKey;
        int size;
    };
    struct DateCheckBox : Date {
        vector<char>* pParams;
        int textureId;
        bool* varible;
        bool GetVarible() {
            return *varible;
        }
        void SetVarible(bool nb) {
            *varible = nb;
        }
    };
    struct DateButton : DateCheckBox {
        string labelKey;
        int size;
        //DateButton() : Date(){};
    };
    struct DateKeyBind : Date {
        int keyNum = 0;
        string stringKey;
        string colorTextKey;
        int size;
    };
    struct DateLabel {
        string* _string;
        //vector<> ;
    };
    struct DateInputPlace : Date {
        int* varible;
        int max;
        int min;
        string textColor;
        int textureId;
    };

    template <typename type>
    struct DateSlider : Date {
        int* varible;
        type min, max;
        int textureid;
        string bgColor, slideColor;

    };

private:
    map_and_keys< string,    bool*      > _parents;
    map_and_keys< string, D3DCOLOR      >  _colors;
    map_and_keys< string, DatePlaces    >  _places;
    map_and_keys< string,   DateText    > _texts;
    map_and_keys< string,    string*    > _labels;
    map_and_keys< string, DateButton    > _buttons;
    map_and_keys< string,DateCheckBox   > _checkboxes;
    map_and_keys< string,     Date      > _lines;
    map_and_keys< string, DateKeyBind   > _keybinds;
    map_and_keys< string, DateInputPlace> _inputplaces;
    map_and_keys< string, DateSlider<int>> _sliders;
};

#endif