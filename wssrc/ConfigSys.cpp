#include "ConfigSys.h"

ConfigSys::ConfigSys(FileSystem* fls, Output* outs) {
    fs=fls; out=outs;
    fs->CreateDir(CFGFOLDER);
    configDate["radarhack"].active = true;
}

bool ConfigSys::Create(string fileName) { return fs->CreateFileInDir(CFGFOLDER, fileName); }

bool ConfigSys::Delete(string fName) { return fs->DeleteFileInDir(fs->GetRootDirrectory(),fName); }

bool ConfigSys::Save(string fName) {

    return true;
}

void ConfigSys::SetDefault() {

}