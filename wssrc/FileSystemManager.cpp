#include "FileSystemManager.h"

bool FileSystemManager::CheckAvalaibleFile(string fileName) {
    fstream file(folderInDirrectory+fileName,ios::in);
    bool answer = file.is_open();
    file.close();
    return answer;
}

bool FileSystemManager::WriteInFile(string fileName, string text) {
    fstream file(folderInDirrectory+fileName, ios::out);
    if(!file.is_open()) {return false;}
    file<<text<<lastLetter;
    file.close();

    return true;
}