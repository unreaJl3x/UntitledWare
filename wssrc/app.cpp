#include "app.h"
#include <string>
#include "ProcessManager.h"
#include "output.h"

using namespace std;

#define INITPARAMSCOUNT 3

App::App(string nameApp, string nameExe, string iCNW) {
    int falseInitCount=0;
    this->nameApp = nameApp;
    this->nameExe = nameExe;
    this->IpClassNameWindow = iCNW;

    this->pId = ProcessManager::GetPID(&nameExe);
    if (!pId) {
        falseInitCount+=2;
        Output::print("'" + nameApp + "' have is Invalid pid.", false, "main");
    } else {
        this->pHandle = ProcessManager::GetHandle(pId);
        if (!pHandle) {
            falseInitCount++;
            Output::print("'" + nameApp + "' invalid handle", false, "main");
        }
    }

    this->hwnd = ProcessManager::GetWindowHandle(&IpClassNameWindow, &nameApp);
    if (!hwnd) {
        falseInitCount++;
        Output::print(("Can't find hwnd at ('"+(IpClassNameWindow)+"', '"+nameApp+"')"),false,"App");
    }

    if (falseInitCount!=0) {
        running = false;
        Output::print("False init '"+nameApp+"'App. ("+to_string(INITPARAMSCOUNT-falseInitCount)+"/"+to_string(INITPARAMSCOUNT)+")",false,"App");
    }
}

void App::SetHeader(string text) {
    SetWindowTextA(this->hwnd, text.c_str());
}

bool App::isRunning() { return running; }

HWND App::GetWindowHandle() { return hwnd; }

std::string App::GetAppName() { return nameApp; }

DWORD App::GetProcessId() { return pId; }

std::string App::GetExeName() { return nameExe; }

std::string App::GetWindowClassName() { return IpClassNameWindow; }

HANDLE App::GetProcessHandle() { return pHandle; }