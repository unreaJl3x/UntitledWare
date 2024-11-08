#include "security.h"
#include "hack.h"

bool Security::Check() {
    DecompleKey dec;
    return dec.decomple(key);
}

void Security::Start()
{
    char username_ [100]; DWORD len = 100; GetUserName(username_, &len);
    string username = username_;
    SetPath("C:\\Users\\"+username+"\\AppData\\Roaming\\UntitledWare\\key.txt");
    fstream file(path, ios::in);
    bool setup = false;

    if(file.is_open())
    {
        char key[100];
        file.getline(key,100,';');
        SetKey(key);
        file.close();
    } else
    {
        string key;
        ofstream filed(path,ios::out);
        getline(cin, key);
        SetKey(key);
        filed << key;
        filed.close();
    }

    if (Check()) {hackIt();}
    else {OUTPUT::print("Invalid key",1,"Security"); remove(path.c_str());}
    return;
}
void Security::SetKey(string key) { this->key = key; }
void Security::SetPath(string path) { this->path = path; }