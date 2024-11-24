#include "configSys.h"

ConfigSys::ConfigSys(string path) { pathToFolder = path;
    CreateDir(pathToFolder); CreateDefaultConfig();}
bool ConfigSys::CreateDir(string path) { return CreateDirectoryA(path.c_str(), NULL); }
bool ConfigSys::CheckAvailableFile(string path) { fstream file(path, ios::in);bool res =file.is_open();file.close();  return res; }

//If File not available returned eRr::0r3::;????
string ConfigSys::ReadFile(string path) {
    fstream file(path, ios::in);
    if(!file.is_open()) {return ERR;}

    char answ[100];
    file.read(answ, 100);
    file.close();

    return answ;
}

bool ConfigSys::WriteInFile(string path, string text) {
    fstream file(path, ios::out);
    if(!file.is_open()) {return ERR;}

    file << text+lastChar;
    file.close();

    return true;
}

bool ConfigSys::loadConfig(string path) {
    fstream file(path, ios::in);
    if (!file.is_open()) {return false;}



    return true;
}
// queue is - Antiflash, RadarHack, FovChanger, GlowESPTeam,GlowESPEnemy
bool ConfigSys::saveConfig(string filename) {
    fstream file(pathToFolder+filename, ios::out);
    if (!file.is_open()) {return false;}

    // ANTIFLASH
    file << dateAntiFlash.active<<lastChar;
    // RADARHACK
    file << dateRadarHack.active<<lastChar;
    // FOVCHANGER
    file << dateFovChanger.active <<(space)<< dateFovChanger.value << lastChar;
    // GLOWESP
    file << dateGlowESP.active <<(space)<< dateGlowESP.TeamRed <<(space)<< dateGlowESP.TeamGreen <<(space)<< dateGlowESP.TeamBlue
    <<(space)<< dateGlowESP.TeamAlpha <<(space)<< dateGlowESP.EnemyRed <<(space)<< dateGlowESP.EnemyGreen <<(space)<< dateGlowESP.EnemyBlue
    <<(space)<< dateGlowESP.EnemyAlpha <<lastChar;

    file.close();

    return true;
}

void ConfigSys::CreateDefaultConfig() {
    this->dateAntiFlash.active = true;
    this->dateRadarHack.active = true;
    this->dateFovChanger.active = true;
    this->dateFovChanger.value = 1220;

    this->dateGlowESP.active = 1;
    this->dateGlowESP.TeamRed = 0;
    this->dateGlowESP.TeamGreen = 1;
    this->dateGlowESP.TeamBlue = 0;
    this->dateGlowESP.TeamAlpha = 1;
    this->dateGlowESP.EnemyRed = 1;
    this->dateGlowESP.EnemyGreen = 0;
    this->dateGlowESP.EnemyBlue = 0;
    this->dateGlowESP.EnemyAlpha = 1;

    saveConfig("default.txt");
}