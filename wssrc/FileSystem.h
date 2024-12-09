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
public:
    void SetRootDirrectory(string);

    bool WriteInFile(string,string,string);
    vector<string> ReadFromFile(string,string);
    bool CreateDir(string);
    bool CreateFileInDir(string,string);

    FileSystem() = default;
    FileSystem(Output*);
    FileSystem(Output*,string);
    FileSystem(string);
};


#endif //UNTITLEDWARE_FILESYSTEM_H
