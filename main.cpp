#include <iostream>

#include "app.h"
#inckude "output.h"
#include "ProcessManager.h"
#include "FileSystemManager.h"
#include "security.h"
using namespace std;

int main(
int argc,
char argv[]
)
 {
if (argc>2) {}
    Output out;
FileSystemManager fm;
Security sec(out, fm);
sec.Start();
    

    return 1;
}