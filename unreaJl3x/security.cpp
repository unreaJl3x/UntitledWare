#include "security.h"


bool Security::Check() {
    DecompleKey dec;
    return dec.decomple(key);
}

void Security::Start()
{
    if(configSys.CheckAvailableFile(path))
    {
        SetKey(configSys.ReadFile(path));
        OUTPUT::print("Load serial keycode",1,"Security");
    } else
    {
        string key;
        OUTPUT::print("Input serial keycode->...",0,"Security");
        getline(cin, key);
        SetKey(key);
        bool keyWrite =configSys.WriteInFile(configSys.pathToFolder+"key.txt", key);
        if(!keyWrite) { OUTPUT::print("Cannot write key in file.",2,"Security"); }
    }

    if (Check()) {SetConsoleTitle("UntitledWare | LICENSED");hackIt();}
    else {OUTPUT::print("Invalid key",1,"Security"); remove(path.c_str());}
    return;
}
void Security::SetKey(string key) { this->key = key; }
Security::Security() {
       path = configSys.pathToFolder+"key.txt";
}