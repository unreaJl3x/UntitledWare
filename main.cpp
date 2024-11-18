#include <iostream>
#include <string>

#include "app.h"
#include "ProcessManager.h"
using namespace std;

int main(
    int argc,
    char* argv[] )
{
    if (argc>2) {}
    Output out;
    ProcessManager csgo(&out,*new App("Counter-Strike: Global Offensive - Direct3D 9","csgo.exe", "Valve001",&out));
    csgo.app.pId = csgo.GetPID();
    csgo.app.pHandle = csgo.GetHandle();
    csgo.app.hwnd = csgo.GetWindowHandle();

    cout<<'"'<<csgo.app.nameApp<<'"'<<" have is id-> "<<to_string(csgo.app.pId)<<", handle-> "<<csgo.app.pHandle<<", hwnd->"<<csgo.app.hwnd<<endl;

    uintptr_t clientDll = csgo.GetModuleAddr("client.dll");
    uintptr_t servDll = csgo.GetModuleAddr("server.dll");
    uintptr_t panaramaDll = csgo.GetModuleAddr("server.dll");

    cout << clientDll << ", " << servDll << ", "<<panaramaDll<<endl;

    return 1;
}