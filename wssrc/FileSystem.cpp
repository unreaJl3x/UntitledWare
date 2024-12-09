#include "FileSystem.h"

FileSystem::FileSystem(Output * output) { out = output; rootDirrectory = CDDIR; }
FileSystem::FileSystem(Output * output, string pathDir) { out = output; rootDirrectory = pathDir; }
FileSystem::FileSystem(string pathDir) {rootDirrectory = pathDir; }

bool FileSystem::CreateDir(string path) { return filesystem::create_directory(path); }

void FileSystem::SetRootDirrectory(string path) { rootDirrectory = path; }

bool FileSystem::CreateFileInDir(string dir, string fileName) {
    if (dir[0] == CDDIR[0] && dir[1] == CDDIR[1]) {
        ofstream file; file.open(dir+"\\"+fileName);
        if (!file.is_open()) {out->print(("Cannot open file from path-> '"+dir+"'"),false,"CreateFile");}

    }
}

bool FileSystem::WriteInFile(string path, string nameFile, string text) {
    ofstream file; file.open(path+"\\"+nameFile);
    if (!file.is_open()) {out->print(("Cannot open file from path-> '"+path+"'"),false,"WriteInFile");return false;}

    file << text;

    file.close();

    return true;
}

vector<string> FileSystem::ReadFromFile(string path, string fileName) {
    ifstream file; file.open(path+"\\"+fileName); string empty="";
    if (!file.is_open()) {out->print(("Cannot open file from path-> '"+path+"'"),false,"ReadFromFile");return *new vector<string>{""};}

    string line;
    vector<string> m;

    while(getline(file, line)) {
        m.push_back(line);
    }

    file.close();
    return m;
}