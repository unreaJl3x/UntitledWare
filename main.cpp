#include <iostream>
#include <string>
#include <thread>

#include "app.h"
#include "FileSystem.h"
#include "ProcessManager.h"
#include "Secure.h"

#include "CSGOCheatFuncsStarter.h"
using namespace std;

int exitt(int code) {
    getchar();
    return code;
}

int main(
    int argc,
    char* argv[] )
{
    if (argc>2) {}
    Output out;
    FileSystem fs(&out, "C:\\UW");
    ProcessManager csgo(&out,*new App("Counter-Strike: Global Offensive - Direct3D 9","csgo.exe", "Valve001",&out));

    csgo.app.pId = csgo.GetPID();
    csgo.app.pHandle = csgo.GetHandle();
    csgo.app.hwnd = csgo.GetWindowHandle();

    if (csgo.app.pId == DWORD(-1) || csgo.app.pHandle == INVALID_HANDLE_VALUE) { out.print("'"+csgo.app.nameApp+"' have is Invalid date.",false,"main"); return exitt(-1); }

    out.print(
            "'" + csgo.app.nameApp + "'" + " have is id-> " + to_string(csgo.app.pId) + ", hwnd->" + to_string( reinterpret_cast<int>( csgo.app.hwnd)),
            1,
            "main"
    );

    Secure sc(&fs,&out);
    if (sc.Start()) {
        CSGOCheatFuncsStarter(&fs,&out,&csgo);
    } else {out.print("Invalid serial key-code.",false,"main");}

    return exitt(1);
}
