#include "MenuController.h"

bool place1 = false;
MenuController::MenuController(dxOverlay* overlay, dxRender* render, bool* menuBool, D3DCOLOR backgroundClor) {
    over = overlay;
    rend = render;

    AddParent(DEFAULT_WINDOWPARENT,          menuBool           );
    AddColor( DEFAULT_WINDOWCOLOR_BACKGROUND, dxRender::COLOR::VERYBLACKGRAY);
    AddColor( "RAINBOW",                     dxRender::COLOR::RED);
    AddColor( "PINK",                     dxRender::COLOR::PINK);
    AddLabel( DEFAULT_TITLELABEL_ID,         DEFAULT_TITLEVALUE  );
    
    CreatePlace(MAIN_WINDOW_NAME, DEFAULT_WINDOWPARENT, &window, DEFAULT_WINDOWCOLOR_BACKGROUND,  new char[1]{DB_FILLED});

    CreatePlace  ("Main.Menu.Outline", DEFAULT_WINDOWPARENT, new RECT(0, 0, window.right, window.bottom), "RAINBOW");
    CreatePlace  ("Main.Menu.Header", DEFAULT_WINDOWPARENT, new RECT(0, 0, window.right, window.bottom*10/100), "RAINBOW", new char[1]{DB_FILLED});
    CreateText   ("Main.MenuHeader.Title", DEFAULT_WINDOWPARENT, DEFAULT_TITLELABEL_ID, DEFAULT_WINDOWCOLOR_BACKGROUND, new RECT(dxRender::width(&window)/3.f,dxRender::height(&window)*2/100,0,0), 25);
    CreateLine   ("Main.Menu.Line1", DEFAULT_WINDOWPARENT, new RECT((dxRender::width(&window)*15/100),window.top,(dxRender::width(&window)*15/100), window.bottom), "RAINBOW");

    AddParent("Place1", &place1);
    AddColor("BLACK", dxRender::COLOR::BLACK);
    CreatePlace  ("Main.Menu.Place1", "Place1", new RECT(dxRender::width(&window)*18/100, dxRender::height(&window)*15/100, dxRender::width(&window)*97/100,dxRender::height(&window)*95/100), "BLACK", new char[1]{DB_FILLED});
    RECT buttonRect(
            dxRender::width(&window)*3/100,
            dxRender::height(&window)*14/100,
            dxRender::width(&window)*12/100,
            0
    );
    CreateButton ("Main.Menu.Misc.Button", DEFAULT_WINDOWPARENT, new RECT(buttonRect.left,buttonRect.top,buttonRect.right,(buttonRect.right-buttonRect.left)+buttonRect.top), &place1,"PINK",new char[1]{DB_OUTLINE});
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

    return _places.Add(placeName, date);
}
bool MenuController::RemovePlace(string keyPlace) {
    return _places.Remove(keyPlace);;
}

void MenuController::Draw() {

    for (string placesKeys : _places._keys) {

        // PLACE
        string placeParent = _places._map[placesKeys].parent;
        if (*(_parents._map[placeParent])==true) {
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
            // LINES
            for (string lineKey : _lines._keys) {
                if (_lines._map[lineKey].parent == placeParent) {
                    RECT lineRect = *_lines._map[lineKey].rect;
                    lineRect.left += window.left;
                    lineRect.top += window.top;
                    lineRect.right += window.left;
                    lineRect.bottom += window.top;

                    rend->drawLine(
                            new POINT(lineRect.left,lineRect.top),
                            new POINT(lineRect.right, lineRect.bottom),
                            _colors._map[_lines._map[lineKey].colorKey]
                    );
                }
            }
            // \LINES
            // TEXT
            for(string textKey : _texts._keys) {
                if (_texts._map[textKey].parent == placeParent) {
                    POINT position(_texts._map[textKey].rect->left, _texts._map[textKey].rect->top);
                    position.x += window.left;
                    position.y += window.top;

                    rend->drawText(
                            &position,
                            _labels._map[_texts._map[textKey].labelKey],
                            _colors._map[_texts._map[textKey].colorKey],
                            _texts._map[textKey].size
                    );
                }
            }
            // \TEXT
            // BUTTON
            for (string buttonKey : _buttons._keys) {
                if (_buttons._map[buttonKey].parent == placeParent) {
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
                        POINT pos (buttonRect.left, buttonRect.top+dxRender::height(&buttonRect)/3.f);
                        rend->drawText(
                                &pos,
                                _labels._map[_buttons._map[buttonKey].labelKey],
                                _colors._map[_buttons._map[buttonKey].colorKey],
                                _buttons._map[buttonKey].size
                        );

                    }
                    rend->Button(&buttonRect, _buttons._map[buttonKey].varible);
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

bool MenuController::CreateText(string textName, string parentName, string labelName, string colorName, RECT* pRect, int size) {
    DateText date;
    date.rect = pRect;
    date.parent = parentName;
    date.size = size;
    date.labelKey = labelName;
    date.colorKey = colorName;

    return _texts.Add(textName, date);
}
bool MenuController::RemoveText(std::string key) {
    return _texts.Remove(key);
}

bool MenuController::CreateButton(string nameButton, string parentName, RECT* r, bool* varible,string colorName, char* pParam, string lableOnButton, int size) {
    DateButton date;
    date.rect = r;
    date.colorKey = colorName;
    date.parent = parentName;
    date.textureId = rend->addTexture(r);
    date.pParams = pParam;
    date.labelKey = lableOnButton;
    date.size = size;
    date.varible = varible;

    return _buttons.Add(nameButton, date);
}
bool MenuController::RemoveButton(std::string key) {
    return _buttons.Remove(key);
}

bool MenuController::CreateLine(string nameLine, string parent, RECT* pos, string colorName) {
    Date date;
    date.parent = parent;
    date.colorKey = colorName;
    date.rect = pos;

    return _lines.Add(nameLine, date);
}
bool MenuController::RemoveLine(string key) {
    return _lines.Remove(key);
}

bool MenuController::CreateCheckBox(string chboxName, string parent,  string colorName, RECT* rect, bool* varible) {
    return true;
}