#include "security.h"
#include "hack.h"
#include "globals.h"

bool Security::Check() {
    DecompleKey dec;
    return dec.decomple(key);
}

void Security::Start()
{
    SetPath(csgo.pathFolder+"\\key.txt");
    fstream file(path, ios::in);
    bool setup = false;

    if(file.is_open())
    {
        char key[100];
        file.getline(key,100,';');
        SetKey(key);
        OUTPUT::print("Load serial keycode",1,"Security");
        file.close();
    } else
    {
        string key;
        ofstream filed(path,ios::out);
        OUTPUT::print("Input serial keycode->...",0,"Security");
        getline(cin, key);
        SetKey(key);
        filed << key;
        filed.close();
    }

    if (Check()) {SetConsoleTitle("UntitledWare | LICENSED");hackIt();}
    else {OUTPUT::print("Invalid key",1,"Security"); remove(path.c_str());}
    return;
}
void Security::SetKey(string key) { this->key = key; }
void Security::SetPath(string path) { this->path = path; }