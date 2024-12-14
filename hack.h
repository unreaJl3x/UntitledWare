#ifndef UNTITLEDWARE_HACK_H
#define UNTITLEDWARE_HACK_H

#include <iostream>
#include <windows.h>
#include <thread>

#include "FileSystem.h"
#include "ProcessManager.h"
#include "output.h"
using namespace std;

class CsgoFuncsHack {
private:
    FileSystem* fs;
    Output* out;
    ProcessManager* csgo;
public:
    void Hack();
    CsgoFuncsHack(FileSystem*, Output*,ProcessManager*);
};

#endif //UNTITLEDWARE_HACK_H
