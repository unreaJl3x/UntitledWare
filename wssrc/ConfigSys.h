#ifndef UNTITLEDWARE_CONFIGSYS_H
#define UNTITLEDWARE_CONFIGSYS_H

#define CFGFOLDER "cfg"
#define CFGEXTENSION "ini"

#include <iostream>

#include "FileSystem.h"
#include "output.h"
using namespace std;

class ConfigSys {
private:
    FileSystem* fs;
    Output* out;
public:
    bool Create(string);
    bool Delete(string);

    bool Load();
    bool Save();

    ConfigSys()=default;
    ConfigSys(FileSystem*, Output*);
};


#endif //UNTITLEDWARE_CONFIGSYS_H
