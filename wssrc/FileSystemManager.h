#ifndef UNTITLEDWARE_FILESYSTEMMANAGER_H
#define UNTITLEDWARE_FILESYSTEMMANAGER_H

#include <fstream>
#include "app.h"

class FileSystemManager : public App {
private:
    char lastLetter = ';';
public:
    string folderInDirrectory="";

    bool CheckAvalaibleFile(string);
    bool WriteInFile(string, string);
};


#endif //UNTITLEDWARE_FILESYSTEMMANAGER_H
