#ifndef UNTITLEDWARE_SECURE_H
#define UNTITLEDWARE_SECURE_H



#include <iostream>
#include <windows.h>
#include <string>

#include "ProcessManager.h"
#include "FileSystem.h"
#include "output.h"
using namespace std;

#define FOLDER "C:\\Users\\"+ProcessManager::GetWindowsUser()+"\\AppData\Local\\UW"
#define KEYFILE "key.txt"

class Secure {
private:
    string key;
    FileSystem* fs;
    Output* out;

public:
    bool Start();
    Secure(FileSystem*, Output*);
};


#endif
