#include <iostream>
#include <fstream>
#include <windows.h>

#include "hack.h"
#include "globals.h"
#include "decomple.h"
#include "unreaJl3x/output.h"
using namespace std;

class Security
{
private:
    string key= "";
    string path;
    bool Check();
    void SetKey(string);
public:
    Security();
    void Start();
};
