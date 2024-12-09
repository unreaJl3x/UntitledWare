#ifndef UNTITLEDWARE_FILESYSTEM_H
#define UNTITLEDWARE_FILESYSTEM_H

#define CDDIR "C:\\"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>

#include "output.h"
using namespace std;

class FileSystem {
private:
    Output* out;
    string rootDirrectory;
    string SlashCheck(string);

public:
    void SetRootDirrectory(string);
    string GetRootDirrectory();

    bool WriteInFile(string,string,string);
    vector<string> ReadFromFile(string,string);
    bool CreateDir(string);
    bool CreateFileInDir(string,string);

    bool DeleteFile(string,string);
    bool DeleteDir(string);

    FileSystem() = default;
    FileSystem(Output*);
    FileSystem(Output*,string);
    FileSystem(string);
};


#endif //UNTITLEDWARE_FILESYSTEM_H
