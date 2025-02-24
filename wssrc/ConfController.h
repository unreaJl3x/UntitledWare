#ifndef CONFCONTROLLER_H
#define CONFCONTROLLER_H

#include <iostream>
#include <windows.h>
#include "thread"
#include "map_and_keys.h"
using namespace std;

class ConfController {
private:
    map_and_keys<int, string> keyList;
public:
    ConfController() {
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
public:
    void GetKeyDown(string*);
};



#endif //CONFCONTROLLER_H
