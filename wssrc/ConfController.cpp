#include "ConfController.h"
#include "dx_interface/dxRender.h"

void GetKey(map_and_keys<int,string>* keyList, string* labelKey) {
    string oldStr = *labelKey;
    *labelKey = "...";
    while (true) {
        for (int keyL : keyList->_keys) {
                *labelKey = (*keyList)[keyL];
                cout << keyL<<endl;
                return;
            if (dxRender::WGetKeyState(keyL)) {
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

