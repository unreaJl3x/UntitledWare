#include "output.h"

void Output::print(string text, int status, string func) {
    cout << litteral << prefix << ":"<< (status==1 ? OK : BAD) << ":" << func << ": " << text << "." << endl;
}