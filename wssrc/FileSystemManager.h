#ifndef UNTITLEDWARE_FILESYSTEMMANAGER_H
#define UNTITLEDWARE_FILESYSTEMMANAGER_H

#include <fstream>
#include <iostream>
#include "output.h"
using namespace std;

class FileSystemManager {
private:
    char lastLetter = ';';
Output* out;

public:
    string folderInDirrectory="";

    bool CheckAvalaibleFile(string);
    bool WriteInFile(string, string);
FileSystemManager(Output*);
};


#endif //UNTITLEDWARE_FILESYSTEMMANAGER_H
