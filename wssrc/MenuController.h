#ifndef UNTITLEDWARE_MENUCONTROLLER_H
#define UNTITLEDWARE_MENUCONTROLLER_H

#include <iostream>
#include <map>
#include <vector>

#include "dx_interface/dxOverlay.h"
#include "dx_interface/dxRender.h"

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
    dxOverlay* over;
    dxRender* rend;

public:
    bool AddParent          ( string key, bool* value );
    bool RemoveParent       ( string key              );

    bool AddColor           ( string key, D3DCOLOR value );
    bool RemoveColor        ( string key                 );
    bool SetColor           ( string key, D3DCOLOR value );
    D3DCOLOR* GetColor      ( string key                 );

    bool AddLabel           ( string key, string value );
    bool RemoveLabel        ( string key               );
    bool SetLabel           ( string key, string value );

    bool CreatePlace        ( string name, string parent, RECT* pPos, string color, vector<char>* pParams = new vector<char>{DB_OUTLINE});
    bool RemovePlace        ( string key);

    bool CreateText         ( string name, string parent, string text, string color, RECT* pos, int size );
    bool RemoveText         ( string key );
    
    bool CreateButton       ( string nameButton, string parent, RECT* pos, bool* varible, string colorName, vector<char>* pParams = new vector<char>{ DB_OUTLINE }, string labelOnButton = "", int size = 0 );
    bool RemoveButton       ( string key );

    bool CreateLine         ( string nameLine, string parent, RECT* pos, string colorName );
    bool RemoveLine         ( string key );

    bool CreateCheckBox     ( string chboxName, string parent,  string colorName, RECT* rect, bool* varible );
    bool RemoveCheckBox     (   );

    bool CreateKeyBind      ( string, string, RECT*, string, string, int );
    bool RemoveKeyBind      ( string);

    bool CreateSlider       (   );
    bool RemoveSlider       (   );

    bool CreateColorPicker  (   );
    bool RemoveColorPicker  (   );

    bool CreateDragBow      (   );
    bool RemoveDragBox      (   );

    bool CreateInputPlace   (   );
    bool RemoveInputPlace   (   );

    void      SetRect   (LONG,LONG,LONG,LONG);
    static RECT* GetRect();

    void Draw();

    MenuController(dxOverlay*, dxRender*, bool*, D3DCOLOR);

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

    template <typename typeKey, typename typeValue>
    class map_and_keys {
    public:
        map<typeKey, typeValue> _map;
        vector<typeKey> _keys;

        typeValue operator [] (typeKey tk) {
            return _map[tk];
        }
        bool Add(typeKey key, typeValue value) {
            for (typeKey k : _keys) {
                if (k==key) { return false; }
            }
            _map[key]=value;
            _keys.push_back(key);
            return true;
        }
        bool Remove(string removeKey) {
            if (_keys.size() == 0) { return false; }
            for (int key = 0; key < _keys.size(); key++) {
                if (_keys[key] == removeKey) {
                    _map.erase(removeKey);
                    _keys.erase(_keys.begin()+key);
                    return true;
                }
            }
            return false;
        }
        bool Set(typeKey keyType, typeValue value) {
            for(string key : _keys) {
                if (key == keyType) {
                    _map[key] = value;
                    return true;
                }
            }
            return false;
        };
    };
    struct Date {
        string colorKey;
        RECT* rect;
        string parent;
    };
    struct DatePlaces : Date {
        vector<char>* pParams;
        int textureId;
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
    };
    struct DateKeyBind : Date {
        int keyNum=0;
        string colorTextKey;
        int size;
    };

private:
    map_and_keys< string,    bool*   > _parents;
    map_and_keys< string, D3DCOLOR  >  _colors;
    map_and_keys< string, DatePlaces >  _places;
    map_and_keys< string,   DateText > _texts;
    map_and_keys< string,    string  > _labels;
    map_and_keys< string, DateButton > _buttons;
    map_and_keys< string,DateCheckBox> _checkboxes;
    map_and_keys< string,     Date   > _lines;
    map_and_keys< string, DateKeyBind> _keybinds;
};

#endif