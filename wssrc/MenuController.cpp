#include "MenuController.h"
#include <thread>
#include <mutex>
#include <string>
#include <conio.h>

bool placeMisc = false;
MenuController::MenuController(dxOverlay* overlay, dxRender* render, bool* menuBool, D3DCOLOR backgroundClor, ConfController* cfc) {
    over = overlay;
    rend = render;
    this->cfc = cfc;

    AddParent(DEFAULT_WINDOWPARENT,          menuBool           );
    AddColor( DEFAULT_WINDOWCOLOR_BACKGROUND, dxRender::COLOR::VERYBLACKGRAY);
    AddColor( "RAINBOW",                     dxRender::COLOR::RED);
    AddColor( "PINK",                     dxRender::COLOR::PINK);
    AddColor( "WHITE",                     dxRender::COLOR::WHITE);
    AddLabel( DEFAULT_TITLELABEL_ID,         new string(DEFAULT_TITLEVALUE)  );
    
    CreatePlace(MAIN_WINDOW_NAME, DEFAULT_WINDOWPARENT, &window, DEFAULT_WINDOWCOLOR_BACKGROUND,  new vector<char>{DB_FILLED});

    CreatePlace  ("Main.Menu.Outline", DEFAULT_WINDOWPARENT, new RECT(0, 0, window.right, window.bottom), "RAINBOW");
    CreatePlace  ("Main.Menu.Header", DEFAULT_WINDOWPARENT, new RECT(0, 0, window.right, window.bottom*10/100), "RAINBOW", new vector<char>{DB_FILLED});
    CreateText   ("Main.MenuHeader.Title", DEFAULT_WINDOWPARENT, DEFAULT_TITLELABEL_ID, DEFAULT_WINDOWCOLOR_BACKGROUND, new RECT(dxRender::width(&window)/3.f,dxRender::height(&window)*2/100,0,0), 25);
    CreateLine   ("Main.Menu.Line1", DEFAULT_WINDOWPARENT, new RECT((dxRender::width(&window)*15/100),window.top,(dxRender::width(&window)*15/100), window.bottom), "RAINBOW");

    AddParent("Place_Misc", &placeMisc);
    AddColor("BLACK", dxRender::COLOR::BLACK);
    CreatePlace  ("Main.Menu.Place1", "Place_Misc", new RECT(dxRender::width(&window)*18/100, dxRender::height(&window)*15/100, dxRender::width(&window)*97/100,dxRender::height(&window)*95/100), "BLACK", new vector<char>{DB_FILLED});
    RECT buttonRect(
            dxRender::width(&window)*3/100,
            dxRender::height(&window)*14/100,
            dxRender::width(&window)*12/100,
            0
    );
    //CreateCheckBox("FovChanger", DEFAULT_WINDOWPARENT,"PINK",new RECT(32,90,64,122), cfc->GetLinkB("FovChanger.active"));
    //CreateInputPlace("fovDate", DEFAULT_WINDOWPARENT, "BLACK",);
    int g = 0;
    CreateSlider("fovDate", DEFAULT_WINDOWPARENT, new RECT(30,100,120,100), 30,"WHITE", "WHITE", &g, 100, 0);

    thread menuDrag(dxRender::CircleDrag, &window, rend->GetHW(), rend->GetTHW(),88,false,false, new POINT[2]{(INT_MAX, INT_MAX),(INT_MAX, INT_MAX)}, RECT(0,0,0,0));
    menuDrag.detach();
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

bool MenuController::CreatePlace(string placeName, string placeParent, RECT* rect, string colorName, vector<char>* pParams) {
    DatePlaces date;
    date.parent = placeParent;
    date.rect = rect;
    date.colorKey = colorName;
    date.pParams = pParams;
    date.textureId = rend->addTexture(rect);

    return _places.Add(placeName, date);
}
bool MenuController::RemovePlace(string keyPlace) {
    return _places.Remove(keyPlace);
}

void MenuController::Draw() {
    for (string placesKeys : _places._keys) {

        // PLACE
        string placeParent = _places._map[placesKeys].parent;
        if (*(_parents._map[placeParent])==true) {
            WRECT placeRect;
            placeRect = _places._map[placesKeys].rect;

            if (placesKeys != MAIN_WINDOW_NAME) {
                placeRect += window;
            }
            rend->drawBox(&placeRect,
                          _colors._map[_places._map[placesKeys].colorKey],
                          _places._map[placesKeys].pParams,
                          new vector<int>{_places._map[placesKeys].textureId});

            // \PLACE
            // LINES
            for (string lineKey : _lines._keys) {
                if (_lines._map[lineKey].parent == placeParent) {
                    WRECT lineRect;
                    lineRect = _lines._map[lineKey].rect;
                    lineRect += placeRect;

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
                    position.x += placeRect.left;
                    position.y += placeRect.top;

                    rend->drawText(
                            &position,
                            *_labels._map[_texts._map[textKey].labelKey],
                            _colors._map[_texts._map[textKey].colorKey],
                            _texts._map[textKey].size
                    );
                }
            }
            // \TEXT
            // BUTTON
            for (string buttonKey : _buttons._keys) {
                if (_buttons._map[buttonKey].parent == placeParent) {
                    WRECT buttonRect;
                    buttonRect = _buttons._map[buttonKey].rect;
                    buttonRect += placeRect;

                    rend->drawBox(
                                &buttonRect,
                                _colors._map[_buttons._map[buttonKey].colorKey],
                                new vector<char>{DB_FILLED,DB_OUTLINE},
                                new vector<int>{ _buttons._map[buttonKey].textureId }
                    );


                    if (_buttons._map[buttonKey].labelKey != "") {
                        POINT pos (buttonRect.left, buttonRect.top+dxRender::height(&buttonRect)/3.f);
                        rend->drawText(
                                &pos,
                                *_labels._map[_buttons._map[buttonKey].labelKey],
                                _colors._map[_buttons._map[buttonKey].colorKey],
                                _buttons._map[buttonKey].size
                        );

                    }
                    if (rend->Button(&buttonRect)) {
                        _buttons[buttonKey].SetVarible(true);
                    }
                }
            }
            // \BUTTON
            // CHECKBOX
            for (string key : _checkboxes._keys) {
                if (_checkboxes[key].parent == placeParent) {
                    WRECT rect;
                    rect = _checkboxes[key].rect;
                    rect += placeRect;

                    if (rend->Button(&rect)) {
                        _checkboxes[key].SetVarible(!*_checkboxes[key].varible);
                    }
                    rend->drawBox(
                        &rect,
                        _colors["PINK"],
                        new vector<char>{(_checkboxes[key].GetVarible()==true) ? DB_FILLED : DB_OUTLINE },
                        new vector<int>{_checkboxes[key].textureId}
                    );

                }
            }
            // \CHECKBOX
            // BINDBOX
            for (string key : _keybinds._keys) {
                if (_keybinds[key].parent == placeParent) {
                    WRECT rect;
                    rect = _keybinds[key].rect;
                    rect += placeRect;
                    static bool getKey = false;
                    if (rend->Button(&rect)) { getKey = true; }
                    if (getKey) {
                        cfc->GetKeyDown(_labels[_keybinds[key].stringKey]);
                        getKey = false;
                    }
                    rend->drawBox(&rect, _colors[_keybinds[key].colorKey] );
                    rend->drawText(new POINT(rect.left,rect.top), *_labels[_keybinds[key].stringKey], _colors[_keybinds[key].colorTextKey], 6);
                }
            }
            // \BINDBOX
            // INPUT PLACE
            /*for (string key : _inputplaces._keys) {
                if (_inputplaces[key].parent == placeParent) {
                    WRECT rect;
                    rect = _inputplaces[key].rect;
                    rect+=placeRect;
                    rend->drawBox(&rect, _colors[_inputplaces[key].colorKey]);
                }
            }*/
            // \INPUT PLACE
            // SLIDER
            for (string key : _sliders._keys) {
                if (_sliders[key].parent == placeParent) {
                    WRECT rect, rectBox;
                    rect = _sliders[key].rect;
                    rect += placeRect;

                    rend->drawLine(new POINT(rect.left,rect.top), new POINT(rect.right,rect.top), _colors[_sliders[key].slideColor]);

                    rectBox = _sliders[key].rectSlide;
                    rectBox += placeRect;
                    rend->drawBox(&rectBox, _colors[_sliders[key].bgColor], new vector<char>{DB_FILLED}, new vector<int>{_sliders[key].textureid});
                    //dxRender::DragRect( _sliders[key].rectSlide,rend->GetHW(),rend->GetTHW(),0, true,false, new POINT[2]{POINT(_sliders[key].rect->left-1,0), POINT(_sliders[key].rect->right+1, 0)},placeRect);

                }
            }
            // \SLIDER
        }
    }
    SetColor("RAINBOW", dxRender::COLOR::Rainbow(*GetColor("RAINBOW")));
    *_labels[DEFAULT_TITLELABEL_ID] = dxRender::ChangingString(DEFAULT_TITLEVALUE, 10);
}

bool MenuController::AddLabel(string labelName, string* varible) {
    return _labels.Add(labelName, varible);
}
bool MenuController::RemoveLabel(string labelName) {
    return _labels.Remove(labelName);
}
bool MenuController::SetLabel(string labelKey, string* value) {

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

bool MenuController::CreateButton(string nameButton, string parentName, RECT* r, bool* varible, string colorName, vector<char>* pParam, string lableOnButton, int size) {
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
    DateCheckBox date;
    date.rect = rect;
    date.varible = varible;
    date.colorKey = colorName;
    date.textureId = rend->addTexture(rect);
    date.parent = parent;
    return _checkboxes.Add(chboxName, date);
}

bool MenuController::CreateKeyBind(string keybindName, string parent, RECT* rect, string colorBoxKey, string colorTextKey, int size, string stringKey) {
    DateKeyBind date;
    date.stringKey = stringKey;
    date.parent = parent;
    date.size = size;
    date.colorTextKey = colorTextKey;
    date.colorKey = colorBoxKey;
    date.rect = rect;
    _labels.Add(stringKey, new string("NONE"));
    return _keybinds.Add(keybindName, date);
}

bool MenuController::RemoveKeyBind(string key) {
    return _keybinds.Remove(key);
}

string MenuController::GetLable(string key) {
    return *_labels[key];
}

/*bool MenuController::CreateInputPlace() {
    DateInputPlace dip;
    dip.max = max;
    dip.min = min;
    dip.varible = varible;
    dip.parent = parent;
    dip.rect = pRect;
    dip.colorKey = colorNameBG;
    dip.textColor = colorNameText;
    dip.textureId = rend->addTexture(pRect);
    return _inputplaces.Add(inputName, dip);
}

bool MenuController::RemoveInputPlace(string key) {
    return _inputplaces.Remove(key);
}
*/
bool MenuController::CreateSlider(string sliderName, string parent, RECT *pRect, LONG size, string bgColor, string slideColor, int *varible, int max, int min) {
    DateSlider<int> date;
    date.max = max;
    date.min = min;
    date.textureid = rend->addTextureFromImage(new RECT(0,0,size,size), "circle.png");
    cout << "Slider" << date.textureid<<endl;
    date.varible = varible;
    date.bgColor = bgColor;
    date.slideColor = slideColor;
    date.parent = parent;
    date.rect = pRect;
    date.size = size;
    date.rectSlide = new RECT(pRect->left+5, pRect->top-(size/2), pRect->left+size+5, pRect->top-(size/2)+size);
    return _sliders.Add(sliderName, date);
}

bool MenuController::RemoveSlider(string k) {
    return _sliders.Remove(k);
}
