#ifndef UNTITLEDWARE_RADARHACK_H
#define UNTITLEDWARE_RADARHACK_H

#include <iostream>
#include <windows.h>

#include "globalDate.h"
#include "csgo_signatures.h"

namespace RadarHack {
    void main() {
        while(true) {
            if (!GLOBAL::cfgSys.configDate["radarhack"].active) {continue;}

            WriteProcessMemory(GLOBAL::AppDate::pHandle, LPVOID(),,sizeof(),NULL);
        }
    }
}

#endif //UNTITLEDWARE_RADARHACK_H
