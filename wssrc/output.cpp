#include "output.h"
#include "windows.h"
using namespace std;

void Output::print(string text, int status, string func) {
    cout << litteral << prefix << ":"<< (status==1 ? OK : BAD) << ":" << func << ":[ " << text << ". ]" << endl;
}

void Output::printWithErrorCode(string text, string func) {
    cout << litteral << prefix << ":"<< (BAD) << ":" << func << ":[ " << text << ". ("<<GetLastError()<<")]" << endl;
}

void Output::printMSG(string text, string title) {
    MessageBoxA(GetActiveWindow(),text.c_str(),title.c_str(),MB_OK);
}