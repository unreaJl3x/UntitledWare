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
        res= filesystem::remove_all(path);
    } catch(...) { res = false; }
    string start = (res?"Successful ":"Cannot ");
    out->print(start+"dirrectory at path->"+path,res,"DeleteDir");
    return res;
}

bool FileSystem::DeleteFileInDir(string path, string fName) {
    bool res;
    try{
        res = filesystem::remove(path+ SlashCheck(path)+fName);
    } catch(...) {res=false;}
    return res;
}

void FileSystem::SetRootDirrectory(string path) { rootDirrectory = path; out->print("Set root dirrectory to'"+rootDirrectory+"'",true,"SetRootDirrectory"); }
string FileSystem::GetRootDirrectory() { return rootDirrectory; }

bool FileSystem::CreateFileInDir(string dir, string fileName) {
   ofstream file; bool localDir = LocalDirCheck(dir);
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
        out->print(("Cannot open file at path-> '"+(!localDir ? dir : rootDirrectory + SlashCheck(rootDirrectory)+dir)+"'"),false,"CreateFileInDir");
        string pathDir =( localDir ? (GetRootDirrectory() + SlashCheck(rootDirrectory) + dir) : ("dir)"));
        out->print("Create dir at path->"+pathDir,false,"CreateFileInDir");

        bool res = CreateDir(pathDir);

        if (!res) { return false; }
    }

    file.close();
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
    ifstream file; file.open((!LocalDirCheck(path)) ? path : (rootDirrectory+SlashCheck(rootDirrectory)+path)
    + SlashCheck(path) + fileName);
    if (!file.is_open()) {out->print(("Cannot open file at path-> '"+path+ SlashCheck(path)+fileName+"'"),false,"ReadFromFile");return *new vector<string>{""};}

    string line;
    vector<string> m;

    while(getline(file, line)) {
        m.push_back(line);
    }

    file.close();
    return m;
}

/// После проверяемой строки
string FileSystem::SlashCheck(std::string stroka) {
    return ((stroka[stroka.length()-1] == '\\') || (stroka[stroka.length()-1] == '/') ? "" : "\\");
}

/// Перед проверяемой строкой
string FileSystem::DotCheck(std::string stroka) {
    return ((stroka[0] == '.') ? "" : ".");
}

bool FileSystem::LocalDirCheck(string path) {
    return (path[0] != CDDIR[0]) && (path[1] != CDDIR[1]);
}

vector<string> FileSystem::GetFileListInDir(string path, string extension) {
    vector<string> files;
    string fName = "temp";
    string fNamePath = "";
    CreateFileInDir(fNamePath,fName);

    for(filesystem::recursive_directory_iterator dir(LocalDirCheck(path) ? (path + SlashCheck(path)):(rootDirrectory + SlashCheck(rootDirrectory) + path +SlashCheck(path))), end; dir!=end;dir++) {
        if (dir->path().extension() != (DotCheck(extension)+extension)) { continue; }

        ofstream file; file.open((LocalDirCheck(path) ? rootDirrectory + SlashCheck(rootDirrectory) + fNamePath:fNamePath) + fName,ios::app);
        file << *dir;
        file.close();
        files = ReadFromFile(fNamePath,fName);
    }
    bool res =DeleteFileInDir(fNamePath,fName);cout << res<<endl;
    return  files;
}

string FileSystem::CreateRandomName(int lenght) {
    random_device rd;   // non-deterministic generator
    mt19937 gen(rd());

    const int sizeAplh = 27;
    char alph[sizeAplh]  = "abcdefghijklmnopqrstuvwxyz";
    string text="";
    for (int i = 0;i<lenght;i++) {

        int r = (gen() % (sizeAplh-2)) +1;

        cout << r<<" "<<alph[r]<<endl;
        text = text + alph[r];
    }
    return text;
}

bool FileSystem::CheckAvaleible(string path, string fName) {
    ifstream file; file.open(LocalDirCheck(path) ?
                        (rootDirrectory +
                        SlashCheck(rootDirrectory) +
                        path +
                        SlashCheck(path) +
                        fName)

                        : (path +
                        SlashCheck(path) +
                        fName)
    );
    bool res = file.is_open();
    file.close();
    return res;
}