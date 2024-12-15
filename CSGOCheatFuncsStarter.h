#ifndef UNTITLEDWARE_CSGOCHEATFUNCSSTARTER_H
#define UNTITLEDWARE_CSGOCHEATFUNCSSTARTER_H

#include <iostream>
#include <windows.h>
#include <thread>

#include "FileSystem.h"
#include "ProcessManager.h"
#include "output.h"
using namespace std;

class CSGOCheatFuncsStarter {
private:
    FileSystem* fs;
    Output* out;
    ProcessManager* csgo;
public:
    void Hack();
    CSGOCheatFuncsStarter(FileSystem*, Output*, ProcessManager*);
};

#endif //UNTITLEDWARE_CSGOCHEATFUNCSSTARTER_H
