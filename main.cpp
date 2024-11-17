#include <iostream>

#include "app.h"
#include "output.h"
#include "ProcessManager.h"
#include "FileSystemManager.h"
//#include "security.h"
using namespace std;

int main(
    int argc,
    char* argv[]
) {
    if (argc>2) {}
    Output out;
    //FileSystemManager fm;
    //Security sec(out, fm);
    //sec.Start();
    App csgo("Counter-Strike", "csgo.exe", "0.0", &out);

    return 1;
}