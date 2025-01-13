#ifndef UNTITLEDWARE_FILESYSTEM_H
#define UNTITLEDWARE_FILESYSTEM_H

#include <iostream>
#include <vector>

#define CDDIR "C:\\"

class FileSystem {
private:
    std::string rootDirrectory;

    static std::string SlashCheck       ( std::string );
    static std::string DotCheck         ( std::string );
    static bool LocalDirCheck           ( std::string );

public:
    bool CheckAvaleible                 ( std::string, std::string );
    static std::string CreateRandomName (      int     );
    void SetRootDirrectory              ( std::string  );
    std::string GetRootDirrectory       (   );

    bool WriteInFile                        ( std::string, std::string, std::string );
    std::vector<std::string> ReadFromFile   (        std::string, std::string       );
    bool CreateDir                          (             std::string               );
    bool CreateFileInDir                    (        std::string, std::string       );

    bool DeleteFileInDir        ( std::string, std::string  );
    bool DeleteDir              (        std::string        );

    std::vector<std::string> GetFileListInDir ( std::string, std::string );

    FileSystem  (               );
    FileSystem  (  std::string  );
};

#endif