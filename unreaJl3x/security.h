#include <iostream>
#include <fstream>
//#include <Lmcons.h>
#include <windows.h>

#include "decomple.h"
#include "unreaJl3x/output.h"
using namespace std;

class Security
{
private:
    string path = "";
    string key="";
    bool Check();
    void SetKey(string);
    void SetPath(string);
public:
    void Start();
};
