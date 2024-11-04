#include "output.h"

namespace OUTPUT {
     /// STATUS CODES -> 0-null, 1-OK, 2-BAD
     bool print(string text, int statuscode, string namef=nullptr) {
          cout  << PREFIX
                << ((statuscode == 0) ? ("") : (statuscode == 1) ? ("OK") : (statuscode == 2) ? ("F"):"ERRORCODE") << ":"
                << ((namef == "0") ? ("") : (namef))
                << ": -> "
                << text
                << endl;
          return 1;
     }
     void print_msg(string text) {
          MessageBox(NULL,text.c_str(),CNAME, MB_OK);
     }
}