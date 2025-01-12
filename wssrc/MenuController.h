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
    bool AddParent(std::string, bool*);
    bool RemoveParent(std::string);

    bool AddColor(std::string, D3DCOLOR);
    bool RemoveColor(std::string);
    bool SetColor(std::string, D3DCOLOR);
    D3DCOLOR* GetColor(std::string);

    bool AddLabel(std::string, std::string);
    bool RemoveLabel(std::string);
    bool SetLabel(std::string, std::string);

    bool CreatePlace(std::string name, std::string parent , RECT*, string color, char* = new char[1]{DB_OUTLINE});
    bool RemovePlace(std::string);

    bool CreateText(std::string name, std::string parent, std::string text, std::string color, RECT, int size);

    bool CreateButton(std::string nameButton, std::string parent, RECT, char*, std::string colorName, std::string labelOnButton, int);
    bool RemoveButton(std::string);

    bool CreateSlider();
    bool RemoveSlider();

    bool CreateDrawBow();
    bool RemoveDragBox();

    void SetRect(LONG,LONG,LONG,LONG);
    static RECT* GetRect();

    void Draw();
    MenuController(dxOverlay*, dxRender*, bool*, D3DCOLOR);

private: // STRUCTS
    template <typename typeKey, typename typeValue>
    class map_and_keys {
    public:
        map<typeKey, typeValue> _map;
        vector<typeKey> _keys;
        bool Add(typeKey key, typeValue value) {
            for (typeKey k : _keys) {
                if (k==key) { return false; }
            }
            _map[key]=value;
            _keys.push_back(key);
            return true;
        }
        bool Remove(std::string removeKey) {
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
    };
    struct Date {
        string colorKey;
        RECT* rect;
        string parent;
    };
    struct DatePlaces : Date {
        char* pParams;
        int textureId;
    };
    struct DateText : Date {
        string labelKey;
        int size;
    };
    struct DateButton : Date{
        /// Can be null
        char* pParams;
        int textureId;
        string labelKey ;
        int size;
    };

private:
    map_and_keys< string,    bool*   > _parents;
    map_and_keys< string, D3DCOLOR  >  _colors;
    map_and_keys< string, DatePlaces >  _places;
    map_and_keys< string,   DateText > _texts;
    map_and_keys< string,    string  > _labels;
    map_and_keys< string, DateButton > _buttons;
};

#endif