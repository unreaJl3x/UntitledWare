#include "FileSystem.h"

FileSystem::FileSystem(Output * output) { out = output; rootDirrectory = CDDIR; }

/// \param pathDir Path to Dirrectory
FileSystem::FileSystem(Output * output, string pathDir) { out = output; rootDirrectory = pathDir; }
FileSystem::FileSystem(string pathDir) {rootDirrectory = pathDir; }

bool FileSystem::CreateDir(string path) {
    bool res;

    try{
        res = filesystem::create_directory(path);
    } catch (...) { res = false; }

    string start = (res?("Has been create"):("Cannot create"));
    out->print(start+" dirrictory at path->"+path,res,"CreateDir");
    return res;
}

bool FileSystem::DeleteDir(string path) {
    bool res;
    try {
        filesystem::remove_all(path);
    } catch(...) { res = false; }
    string start = ;
}

void FileSystem::SetRootDirrectory(string path) { rootDirrectory = path; out->print("Set root dirrectory to'"+rootDirrectory+"'",true,"SetRootDirrectory"); }
string FileSystem::GetRootDirrectory() { return rootDirrectory; }

bool FileSystem::CreateFileInDir(string dir, string fileName) {
   ofstream file;
   const bool localDir = dir[0] != CDDIR[0] && dir[1] != CDDIR[1];
    if (!localDir) {
         file.open(
                dir+
                SlashCheck(dir)+
                fileName );
    } else {
        file.open(
                rootDirrectory+
                SlashCheck(rootDirrectory) +
                dir+
                SlashCheck(dir)+
                fileName);
    }
    if (!file.is_open()) {
        out->print(("Cannot open file at path-> '"+(!localDir ? dir : rootDirrectory + SlashCheck(rootDirrectory)+dir)+"'"),false,"CreateFile");
        string pathDir =( localDir == true ? (GetRootDirrectory() + SlashCheck(rootDirrectory) + dir) : ("dir)"));
        out->print("Create dir at path->"+pathDir,false,"CreateFileFromDir");

        bool res = CreateDir(pathDir);

        if (!res) { return false; }
    }

    return true;
}

bool FileSystem::WriteInFile(string path, string nameFile, string text) {
    ofstream file; file.open(path+"\\"+nameFile);
    if (!file.is_open()) {out->print(("Cannot open file at path-> '"+path+"'"),false,"WriteInFile");return false;}

    file << text;

    file.close();

    return true;
}

vector<string> FileSystem::ReadFromFile(string path, string fileName) {
    ifstream file; file.open(path+"\\"+fileName);
    if (!file.is_open()) {out->print(("Cannot open file at path-> '"+path+"'"),false,"ReadFromFile");return *new vector<string>{""};}

    string line;
    vector<string> m;

    while(getline(file, line)) {
        m.push_back(line);
    }

    file.close();
    return m;
}

string FileSystem::SlashCheck(std::string stroka) {
    return ((stroka[stroka.length()-1] == '\\') || (stroka[stroka.length()-1] == '/') ? "" : "\\");
}