#ifndef UNTITLEDWARE_CONFIGSYS_H
#define UNTITLEDWARE_CONFIGSYS_H

#define CFGFOLDER "cfg"
#define CFGEXTENSION "ini"

#include <iostream>
#include <map>
#include "FileSystem.h"
#include "output.h"
using namespace std;

class ConfigSys {
private:
    FileSystem* fs;
    Output* out;

public:
    struct Date {
        bool active;
    };

    map<string, Date> configDate;

    bool Create(string);
    bool Delete(string);

    bool Load();
    bool Save(string);

    void SetDefault();

    ConfigSys()=default;
    ConfigSys(FileSystem*, Output*);
};


#endif //UNTITLEDWARE_CONFIGSYS_H
