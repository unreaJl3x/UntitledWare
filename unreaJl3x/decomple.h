#include <iostream>
using namespace std;

class DecompleKey
{
private:
    int ALPHA = 25;
    char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char nums[10] = {'0','1', '2', '3', '4', '5', '6', '7', '8', '9'};
    template<int size>
    bool CheckLetter(char*,char letter);
    int GetLetterPos(char);
public:
    bool decomple(string key);
};