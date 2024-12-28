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
    class Date {
    public:
        bool active;

        void main();
        void returned();
    };
    // FUNCS DATE
    struct GlowEspDate : Date {
        unsigned __int8 rgb[2][3];
    };
    struct RadarHackDate : Date {};
    struct FovChangerDate : Date {
        unsigned __int8 fov = 180;
    };

public:
    map<string, Date> configDate;
    bool Create(string);
    bool Delete(string);

    bool Load();
    bool Save(string);

    void SetDefault();

    ConfigSys()=default;
    ConfigSys(FileSystem*);
};


#endif //UNTITLEDWARE_CONFIGSYS_H
