#include "ConfigSys.h"

ConfigSys::ConfigSys(FileSystem* fls, Output* outs) { fs=fls; out=outs; fs->CreateDir(CFGFOLDER); }

bool ConfigSys::Create(string fileName) {
    fs->CreateFileInDir(CFGFOLDER, fileName);
    return true;
}

bool ConfigSys::Delete(string fName) {
    fs->DeleteFileInDir(fs->GetRootDirrectory(),fName);
    return true;
}

bool ConfigSys::Save() {


    return true;
}