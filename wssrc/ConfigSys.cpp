#include "ConfigSys.h"

ConfigSys::ConfigSys(FileSystem* fls, Output* outs) { fs=fls; out=outs; fs->CreateDir(CFGFOLDER); }

bool ConfigSys::Create(string fileName) { return fs->CreateFileInDir(CFGFOLDER, fileName); }

bool ConfigSys::Delete(string fName) { return fs->DeleteFileInDir(fs->GetRootDirrectory(),fName); }

bool ConfigSys::Save(Date d, string fName) {
    bool res = fs->WriteInFile(CFGFOLDER, fName, to_string(d.i1));
    if (!res) {bool res2 = fs->CreateFileInDir(CFGFOLDER,fName); if (res2) {res = fs->WriteInFile(CFGFOLDER, fName, to_string(d.i1));}}

    return res;
}