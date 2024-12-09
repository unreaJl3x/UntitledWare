#include "ConfigSys.h"

ConfigSys::ConfigSys(FileSystem* fls, Output* outs) { fs=fls; out=outs; }

bool ConfigSys::Create(string fileName) {
    fs->CreateFileInDir(CFGFOLDER, fileName);
    return true;
}

bool ConfigSys::Delete(string fileName) {
    fs->
    return true;
}