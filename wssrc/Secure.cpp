#include "Secure.h"
#include "decomple.h"

Secure::Secure(FileSystem* f) {fs=f;}

bool Secure::Start() {
    string testkey;
    if (!fs->CheckAvaleible(FOLDER,KEYFILE)) {
        cin >> testkey;
        bool resDir = fs->CreateFileInDir(FOLDER,KEYFILE); if (!resDir) { Output::print("Cannot create file at path.",resDir,"Secure.Start"); }
        bool resWrite = fs->WriteInFile(FOLDER,KEYFILE,testkey); if (!resWrite) { Output::print("Cannot write key in file.",resWrite,"Secure.Start"); }
    }
    else { testkey = fs->ReadFromFile(FOLDER,KEYFILE)[0]; }

    DecompleKey dk;
    return dk.decomple(key);
}