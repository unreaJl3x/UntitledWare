#ifndef UNTITLEDWARE_OUTPUT_H
#define UNTITLEDWARE_OUTPUT_H

#include <iostream>

#define BAD "FF"
#define OK "OK"

class Output {
private:
    static inline const std::string litteral = "|*> ";
    static inline const std::string prefix ="UW";

public:
    static void print               ( std::string, int, std::string );
    static void printWithErrorCode  ( std::string, std::string      );
    static void printMSG            ( std::string, std::string      );
};


#endif //UNTITLEDWARE_OUTPUT_H
