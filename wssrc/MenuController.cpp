#include "MenuController.h"

MenuController::MenuController(dxOverlay* overlay, dxRender* render, bool* menuBool, D3DCOLOR backgroundClor) {
    over = overlay;
    rend = render;

    AddParent(DEFAULT_WINDOWPARENT,          menuBool           );
    AddColor( DEFAULT_WINDOWCOLOR_BACKGROUND, dxRender::COLOR::PINK     );
    AddColor( "RAINBOW",                     dxRender::COLOR::RED);
    AddLabel( DEFAULT_TITLELABEL_ID,         DEFAULT_TITLEVALUE  );
    
    CreatePlace(MAIN_WINDOW_NAME, DEFAULT_WINDOWPARENT, &window, DEFAULT_WINDOWCOLOR_BACKGROUND,  new char[1]{DB_FILLED});

    CreatePlace("MainMenuOutline", DEFAULT_WINDOWPARENT, new RECT(0, 0, window.right, window.bottom), "RAINBOW");
    CreatePlace("MainMenuHeader", DEFAULT_WINDOWPARENT, new RECT(0, 0, window.right, window.bottom*10/100), "RAINBOW", new char[1]{DB_FILLED});
    CreateText("MainMenuHeaderTitle", DEFAULT_WINDOWPARENT, DEFAULT_TITLELABEL_ID, DEFAULT_WINDOWCOLOR_BACKGROUND, RECT(dxRender::width(&window)/3.f,dxRender::height(&window)*2/100,0,0), 25);

}

void MenuController::SetRect(LONG x, LONG y, LONG w, LONG h) {
    window.left = x;
    window.top = y;
    window.right = w;
    window.bottom = h;
}
RECT* MenuController::GetRect() { return &window; }

bool MenuController::AddParent(string parentName, bool* drawParent) {
    return _parents.Add(parentName,drawParent);
}
bool MenuController::RemoveParent(string parentName) {
    return _parents.Remove(parentName);
}

bool MenuController::AddColor(string colorKey, D3DCOLOR pColor) {
    return _colors.Add(colorKey, pColor);;
}
bool MenuController::RemoveColor(string colorKey) {
    return _colors.Remove(colorKey);
}
bool MenuController::SetColor(string keyColor, D3DCOLOR newColor) {
    return _colors.Set(keyColor, newColor);
}
D3DCOLOR* MenuController::GetColor(string colorKey) {
    return &_colors._map[colorKey];
}

bool MenuController::CreatePlace(string placeName, string placeParent, RECT* rect, string colorName, char* pParams) {
    DatePlaces date;
    date.parent = placeParent;
    date.rect = rect;
    date.colorKey = colorName;
    date.pParams = pParams;
    date.textureId = rend->addTexture(rect);

    _places.Add(placeName, date);

    return true;
}
bool MenuController::RemovePlace(string keyPlace) {
    return _places.Remove(keyPlace);;
}

void MenuController::Draw() {

    for (string placesKeys : _places._keys) {

        // PLACE
        if (*(_parents._map[_places._map[placesKeys].parent])==true) {
            RECT placeRect = *_places._map[placesKeys].rect;
            if (placesKeys != MAIN_WINDOW_NAME) {
                placeRect.left += window.left;
                placeRect.top += window.top;
                placeRect.right += window.left;
                placeRect.bottom += window.top;
            }
            rend->drawBox(&placeRect,
                          _colors._map[_places._map[placesKeys].colorKey],
                          _places._map[placesKeys].pParams,
                          new vector<int>{_places._map[placesKeys].textureId});

            // \PLACE
            // TEXT
            for(string textKey : _texts._keys) {
                if (_texts._map[textKey].parent == _places._map[placesKeys].parent) {
                    POINT position(_texts._map[textKey].rect->left, _texts._map[textKey].rect->top);
                    position.x += window.left;
                    position.y += window.top;

                    rend->drawText(
                            &position,
                            "_labels._map[_texts._map[textKey].labelKey]",
                            dxRender::COLOR::BLACK,
                            25
                    );
                    cout << "key: " << textKey << "| label: " << _labels._map[_texts._map[textKey].labelKey]<<"| size: "<<_texts._map[textKey].size<<endl;

                }
            }
            // \TEXT
            // BUTTON
            for (string buttonKey : _buttons._keys) {
                if (_buttons._map[buttonKey].parent == _places._map[placesKeys].parent) {
                    RECT buttonRect = *_buttons._map[buttonKey].rect;

                    buttonRect.left   += window.left;
                    buttonRect.top    += window.top;
                    buttonRect.right  += window.left;
                    buttonRect.bottom += window.top;

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
            // \BUTTON
        }
    }

    SetColor("RAINBOW", dxRender::COLOR::Rainbow(*GetColor("RAINBOW")));
    SetLabel(DEFAULT_TITLELABEL_ID, dxRender::ChangingString(DEFAULT_TITLEVALUE, 10));
    rend->DragMenu(&window);
}

bool MenuController::AddLabel(string labelName, string varible) {
    return _labels.Add(labelName, varible);
}
bool MenuController::RemoveLabel(string labelName) {
    return _labels.Remove(labelName);
}
bool MenuController::SetLabel(string labelKey, string value) {
    return _labels.Set(labelKey, value);
}

bool MenuController::CreateText(string textName, string parentName, string labelName, string colorName, RECT pRect, int size) {
    DateText date;
    date.rect = &pRect;
    date.parent = parentName;
    date.size = size;
    date.labelKey = labelName;
    date.colorKey = colorName;

    _texts.Add(textName, date);
    return true;
}

bool MenuController::CreateButton(string nameButton, string parentName, RECT r, string colorName, char* pParam, string lableOnButton, int size) {
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