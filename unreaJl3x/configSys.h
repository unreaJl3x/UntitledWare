#ifndef UNTITLEDWARE_CONFIGSYS_H
#define UNTITLEDWARE_CONFIGSYS_H

#define ERR "eRr::0r3::;????"

#include <iostream>
#include <fstream>
#include <windows.h>
#include "output.h"
using namespace std;

class ConfigSys {
private:
    char space = ' ';
    char lastChar = ';';
    struct DateOfAntoFlash {
        bool active = true;
    };
    struct DateOfFovChanger {
        bool active = true;
        int value = 180;
    };
    struct DateOfRadarHack {
        bool active = true;
    };
    struct DateOfGlowESP {
        bool active;
        int EnemyRed=1,EnemyGreen=0,EnemyBlue=0,EnemyAlpha=1;
        int TeamRed=0,TeamGreen=1,TeamBlue=0,TeamAlpha=1;
    };
    void CreateDefaultConfig();
public:
    DateOfAntoFlash dateAntiFlash;
    DateOfFovChanger dateFovChanger;
    DateOfRadarHack dateRadarHack;
    DateOfGlowESP dateGlowESP;

    string pathToFolder;

    bool CreateDir(string);
    string ReadFile(string);
    bool WriteInFile(string,string);
    bool CheckAvailableFile(string);
    bool loadConfig(string);
    bool saveConfig(string);

    ConfigSys() = default;
    ConfigSys(string);
};


#endif
