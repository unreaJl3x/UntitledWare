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

    DWORD pId = NULL;
    HANDLE pHandle = nullptr;
    HWND hwnd = nullptr;

    bool running;

public:
    bool isRunning();
    DWORD GetProcessId();
    std::string GetAppName();
    std::string GetExeName();
    std::string GetWindowClassName();
    HANDLE GetProcessHandle();
    HWND GetWindowHandle();

    void SetHeader(std::string);
    App(std::string, std::string, std::string);
};


#endif
