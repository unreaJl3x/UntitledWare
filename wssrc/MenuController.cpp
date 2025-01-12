#include "MenuController.h"

MenuController::MenuController(dxOverlay* overlay, dxRender* render, bool* menuBool, D3DCOLOR backgroundClor) {
    over = overlay;
    rend = render;

    AddParent(DEFAULT_WINDOWPARENT, menuBool);
    AddColor(DEFAULT_WINDOWCOLOR_BACKGROUND, backgroundClor);
    AddLabel(DEFAULT_TITLELABEL_ID, DEFAULT_TITLEVALUE);
    CreatePlace(MAIN_WINDOW_NAME, DEFAULT_WINDOWPARENT, &window, DEFAULT_WINDOWCOLOR_BACKGROUND, new char[1]{DB_FILLED});
}

void MenuController::SetRect(LONG x, LONG y, LONG w, LONG h) {
    window.left = x;
    window.top = y;
    window.right = w;
    window.bottom = h;
}
RECT* MenuController::GetRect() { return &window; }

bool MenuController::AddParent(std::string parentName, bool* drawParent) {
    for (string key : _parents._keys) {
        if( key == parentName ) { return false; }
    }
    _parents.Add(parentName,drawParent);
    return true;
}

bool MenuController::RemoveParent(std::string parentName) {
    return _parents.Remove(parentName);
}

bool MenuController::AddColor(std::string colorKey, D3DCOLOR pColor) {
    for( string key : _colors._keys) {
        if (key == colorKey) {
            return false;
        }
    }
    _colors.Add(colorKey, pColor);
    return true;
}

bool MenuController::RemoveColor(std::string colorKey) {
    return _colors.Remove(colorKey);
}

bool MenuController::SetColor(std::string keyColor, D3DCOLOR newColor) {
    for(string key : _colors._keys) {
        if (key == keyColor) {
            _colors._map[keyColor] = newColor;
            return true;
        }
    }
    return false;
}

D3DCOLOR* MenuController::GetColor(std::string colorKey) {
    return &_colors._map[colorKey];
}

bool MenuController::CreatePlace(std::string placeName, std::string placeParent, RECT* rect, std::string colorName, char* pParams) {
    if ( _parents._keys.size() == 0 ) { return false; }
    for ( string key : _places._keys ) {
        if ( key == placeName ) { return false; }
    }

    DatePlaces date;
    date.parent = placeParent;
    date.rect = rect;
    date.colorKey = colorName;
    date.pParams = pParams;
    date.textureId = rend->addTexture(rect);

    _places.Add(placeName, date);

    return true;
}

bool MenuController::RemovePlace(std::string keyPlace) {
    return _places.Remove(keyPlace);;
}

void MenuController::Draw() {
    for (string placesKeys : _places._keys) {
        if (*(_parents._map[_places._map[placesKeys].parent])==true) {
            RECT placeRect = *_places._map[placesKeys].rect;
            if (placesKeys != MAIN_WINDOW_NAME) {
                placeRect.left   += window.left;
                placeRect.top    += window.top;
                placeRect.right  += window.left;
                placeRect.bottom += window.top;
            }
            rend->drawBox(&placeRect,
                          _colors._map[_places._map[placesKeys].colorKey],
                          _places._map[placesKeys].pParams,
                          new vector<int>{_places._map[placesKeys].textureId});
            for(string textKey : _texts._keys) {
                if (_texts._map[textKey].parent == _places._map[placesKeys].parent) {
                    rend->drawText(
                            new POINT(window.left + _texts._map[textKey].rect->left,window.top+_texts._map[textKey].rect->top),
                            _labels._map[_texts._map[textKey].labelKey],
                            _colors._map[_texts._map[textKey].colorKey],
                            _texts._map[textKey].size
                    );
                }
            }
            for (string buttonKey : _buttons._keys) {
                if (_buttons._map[buttonKey].parent == _places._map[placesKeys].parent) {
                    RECT buttonRect;
                    cout <<  + _buttons._map[buttonKey].rect->left<<endl;
                    buttonRect.left = window.left + _buttons._map[buttonKey].rect->left;
                    buttonRect.top = window.top + _buttons._map[buttonKey].rect->top;
                    buttonRect.right = window.left + _buttons._map[buttonKey].rect->right;
                    buttonRect.bottom = window.top + _buttons._map[buttonKey].rect->bottom;
                    rend->drawBox(
                                &buttonRect,
                                _colors._map[_buttons._map[buttonKey].colorKey],
                                _buttons._map[buttonKey].pParams,
                                new vector<int>{ _buttons._map[buttonKey].textureId }
                    );
                    if (_buttons._map[buttonKey].labelKey != "") {
                        rend->drawText(
                                new POINT(dxRender::width(&placeRect)/6.f,dxRender::height(&placeRect)/6.f),
                                _labels._map[_buttons._map[buttonKey].labelKey],
                                _colors._map[_buttons._map[buttonKey].colorKey],
                                dxRender::width(&placeRect)/6.f
                        );
                    }
                }
            }
        }

    }
    rend->DragMenu(&window);
}

bool MenuController::AddLabel(std::string labelName, std::string varible) {
    for (string key : _labels._keys) {
        if (key == labelName) { return false; }
    }
    _labels.Add(labelName, varible);
    return true;
}

bool MenuController::RemoveLabel(std::string labelName) {
    return _labels.Remove(labelName);
}

bool MenuController::SetLabel(std::string labelKey, std::string value) {
    for (string key : _labels._keys) {
        if (key == labelKey) {
            _labels._map[key] = value;
            return true;
        }
    }
    return false;
}

bool MenuController::CreateText(std::string textName, std::string parentName, std::string labelName, std::string colorName, RECT pRect, int size) {
    for (string key : _texts._keys) {
        if (textName == key) { return false; }
    }

    DateText date;
    date.rect = &pRect;
    date.parent = parentName;
    date.size = size;
    date.labelKey = labelName;
    date.colorKey = colorName;

    _texts.Add(textName, date);
    return true;
}

bool MenuController::CreateButton(std::string nameButton, std::string parentName, RECT r, char *pParam, std::string colorName, std::string lableOnButton, int size) {
    for (string key : _buttons._keys) {
        if (nameButton == key) { return false; }
    }

    DateButton date;
    date.rect = &r;
    date.colorKey = colorName;
    date.parent = parentName;
    date.textureId = rend->addTexture(&r);
    date.pParams = pParam;
    date.labelKey = lableOnButton;
    date.size = size;

    _buttons.Add(nameButton, date);
    return true;
}