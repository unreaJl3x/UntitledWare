#ifndef UNTITLEDWARE_APPCS_H
#define UNTITLEDWARE_APPCS_H

#include <map>
#include "app.h"
#include "ProcessManager.h"

class AppCS : public App {
public:
    map<string,uintptr_t> dllAddress;

    AppCS() : App("Counter-Strike: Global Offensive - Direct3D 9", "csgo.exe", "Valve001") {
        dllAddress["client.dll"] = ProcessManager::GetModuleAddr("client.dll", pId);
    };
};


#endif
