#ifndef UNTITLEDWARE_FILESYSTEM_H
#define UNTITLEDWARE_FILESYSTEM_H

#define CDDIR "C:\\"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <random>

#include "output.h"
using namespace std;

class FileSystem {
private:
    Output* out;
    string rootDirrectory;
    string SlashCheck(string);
    string DotCheck(string);
    bool LocalDirCheck(string);

public:

    string CreateRandomName(int);
    void SetRootDirrectory(string);
    string GetRootDirrectory();

    bool WriteInFile(string,string,string);
    vector<string> ReadFromFile(string,string);
    bool CreateDir(string);
    bool CreateFileInDir(string,string);

    bool DeleteFileInDir(string,string);
    bool DeleteDir(string);

    vector<string> GetFileListInDir(string, string);

    FileSystem() = default;
    FileSystem(Output*);
    FileSystem(Output*,string);
    FileSystem(string);
};


#endif //UNTITLEDWARE_FILESYSTEM_H
