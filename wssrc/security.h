#ifndef UNTITLEDWARE_SECURITY
#define UNTITLEDWARE_SECURITY

#include <iostream>

//#include "decomple.h"
#include "output.h"

using namespace std;

class Security {
private:
Output* out;
FileSystemManager*fm;
bool CheckValid();
string key;

public:
void Start();
Secure(Output*,FileSystemManager*);
}
#endef