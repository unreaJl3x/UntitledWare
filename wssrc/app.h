#ifndef UNTITLEDWARE_APP_H
#define UNTITLEDWARE_APP_H

#include <iostream>
#include <windows.h>

class App {
private:
    int resolution[2];
    std::string nameApp;
    std::string nameExe;
    std::string IpClassNameWindow;

    HANDLE pHandle;
    DWORD pId;
    HWND hwnd;

    bool running;

public:
    bool isRunning                  (   );
    DWORD GetProcessId              (   );
    std::string GetAppName          (   );
    std::string GetExeName          (   );
    std::string GetWindowClassName  (   );
    HANDLE GetProcessHandle         (   );
    HWND GetWindowHandle            (   );

    void SetHeader  ( std::string );
    App             ( std::string, std::string, std::string );
};

#endif