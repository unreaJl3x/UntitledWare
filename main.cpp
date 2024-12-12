#include <iostream>
#include <string>

#include "app.h"
#include "FileSystem.h"
#include "ProcessManager.h"
#include "GUI.h"
using namespace std;

int main(
    int argc,
    char* argv[] )
{
    if (argc>2) {}
    Output out;
    /*ProcessManager csgo(&out,*new App("Counter-Strike: Global Offensive - Direct3D 9","csgo.exe", "Valve001",&out));

    csgo.app.pId = csgo.GetPID();
    csgo.app.pHandle = csgo.GetHandle();
    csgo.app.hwnd = csgo.GetWindowHandle();

    out.print(
            "'" + csgo.app.nameApp + "'" + " have is id-> " + to_string(csgo.app.pId) + ", hwnd->" + to_string( reinterpret_cast<int>( csgo.app.hwnd)),
            1,
            "main"
    );

    uintptr_t clientDll = csgo.GetModuleAddr("client.dll");
    uintptr_t servDll = csgo.GetModuleAddr("server.dll");
    uintptr_t panaramaDll = csgo.GetModuleAddr("server.dll");

    cout << clientDll << ", " << servDll << ", "<<panaramaDll<<endl;
    */
    FileSystem fs(&out,"C:\\UW");
    fs.CreateFileInDir("cfg",fs.CreateRandomName(5)+".txt");


    vector<string> test = fs.GetFileListInDir("cfg","txt");
    for(string i : test) {
        cout << i << endl;
    }

    return 1;
}
