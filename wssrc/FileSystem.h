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
    string rootDirrectory;

    static string SlashCheck(string);
    static string DotCheck(string);
    static bool LocalDirCheck(string);

public:
    bool CheckAvaleible(string, string);
    static string CreateRandomName(int);
    void SetRootDirrectory(string);
    string GetRootDirrectory();

    bool WriteInFile(string,string,string);
    vector<string> ReadFromFile(string,string);
    bool CreateDir(string);
    bool CreateFileInDir(string,string);

    bool DeleteFileInDir(string,string);
    bool DeleteDir(string);

    vector<string> GetFileListInDir(string, string);

    FileSystem();
    FileSystem(string);
};


#endif //UNTITLEDWARE_FILESYSTEM_H
