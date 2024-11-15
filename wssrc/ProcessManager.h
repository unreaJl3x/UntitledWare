#ifndef UNTITLEDWARE_PROCESSMANAGER_H
#define UNTITLEDWARE_PROCESSMANAGER_H

#include <iostream>
#include <windows.h>
#include <Tlhelp32.h>

#include "output.h"
#include "app.h"
#include "FileManager.h"
using namespace std;

class ProcessManager {
private:
Output* out;
App* victim;

public:
bool Write();
template <typename T>
T Read();
ProcessManager(Output*,App*);
};

#endif //UNTITLEDWARE_PROCESSMANAGER_H
