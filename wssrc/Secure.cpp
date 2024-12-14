#include "Secure.h"
#include "decomple.h"

Secure::Secure(FileSystem* f, Output* o) {fs=f; out = o;}

bool Secure::Start() {
    string testkey;
    if (!fs->CheckAvaleible(FOLDER,KEYFILE)) {
        cin >> testkey;
        bool resDir = fs->CreateFileInDir(FOLDER,KEYFILE); if (!resDir) { out->print("Cannot create file at path.",resDir,"Secure.Start"); }
        bool resWrite = fs->WriteInFile(FOLDER,KEYFILE,testkey); if (!resWrite) { out->print("Cannot write key in file.",resWrite,"Secure.Start"); }
    }
    else { testkey = fs->ReadFromFile(FOLDER,KEYFILE)[0]; }

    DecompleKey dk;
    return dk.decomple(key);
}