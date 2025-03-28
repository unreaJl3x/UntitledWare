#include "ConfController.h"

#include <string>

#include "dx_interface/dxRender.h"
#define KEY1 date._keys[0]
void GetKey(map_and_keys<int,string>* keyList, string* labelKey) {
    string oldStr = *labelKey;
    *labelKey = "...";
    while (true) {
        for (int keyL : keyList->_keys) {
            if (dxRender::WGetKeyState(keyL)) {
                *labelKey = (*keyList)[keyL];
                return;
            } else if (dxRender::WGetKeyState(VK_ESCAPE)) {
                *labelKey = oldStr;
                return;
            }
        }
    }
    return;
}

void ConfController::GetKeyDown(string* key) {
    thread keygetter(GetKey, &keyList, key);
    keygetter.detach();
}

void ConfController::InitKeys() {
    //keyList.Add(0x01, "VK_LBUTTON");
    keyList.Add(0x02, "VK_RBUTTON");
    keyList.Add(0x41, "A");
    keyList.Add(0x42, "B");
    keyList.Add(0x43, "C");
    keyList.Add(0x44, "D");
    keyList.Add(0x45, "E");
    keyList.Add(0x46, "F");
    keyList.Add(0x47, "G");
    keyList.Add(0x48, "H");
    keyList.Add(0x49, "I");
    keyList.Add(0x4A, "J");
    keyList.Add(0x4B, "K");
    keyList.Add(0x4C, "L");
    keyList.Add(0x4D, "M");
    keyList.Add(0x4E, "N");
    keyList.Add(0x4E, "N");
    keyList.Add(0x4F, "O");
    keyList.Add(0x50, "P");
    keyList.Add(0x51, "Q");
    keyList.Add(0x52, "R");
    keyList.Add(0x53, "S");
    keyList.Add(0x54, "T");
    keyList.Add(0x55, "U");
    keyList.Add(0x56, "Y");
    keyList.Add(0x57, "W");
    keyList.Add(0x58, "X");
    keyList.Add(0x59, "Y");
    keyList.Add(0x5A, "Z");
}


bool* ConfController::GetLinkB(string key) {
    string keyF = key.substr(0,key.find('.'));
    string keyS = key.substr(key.find('.')+1, key.length()-1);

    if (keyF == date._map[KEY1].dateFov.dateIndf) {
        if (keyS=="active") {
            return &(date._map[KEY1].dateFov.active);
        }
    } else if (keyF == date._map[KEY1].radarHack.dateIndf) {
        if (keyS == "active") {
            return &(date._map[KEY1].radarHack.active);
        }
    }

    return nullptr;
}
int* ConfController::GetLinkI(string key) {
    string keyF = key.substr(0,key.find('.'));
    string keyS = key.substr(key.find('.')+1, key.length()-1);

    if (keyF == date._map[KEY1].dateFov.dateIndf) {
        if (keyS == "fovValue") {
            return &(date._map[KEY1].dateFov.fovValue.mValue);
        } else if (keyS == "fovValueD") {
            return &(date._map[KEY1].dateFov.fovValue.dValue);
        }
    }
    return nullptr;
}
