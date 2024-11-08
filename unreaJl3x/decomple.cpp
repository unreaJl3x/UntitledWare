#include "decomple.h"
#define EMPTY ' '
bool DecompleKey::decomple(string key)
{
    string sort[3];
    int sum = 0;
    sort[0] = key.substr(0, key.find(EMPTY));
    key.erase(0, key.find(EMPTY) + 1);
    sort[1] = key.substr(0, key.find(EMPTY));
    key.erase(0, key.find(EMPTY) + 1);
    sort[2] = key.substr(0, key.find(EMPTY));;
    for(int p = 0; p <3; p++)
    {
        string temp = "";
        for (int y = 0; y<sort[p].length(); y++)
        {
            if (!CheckLetter<10>(nums, sort[p][y]))
            {
                temp+=tolower(sort[p][y]);
            }
        }
        temp = temp.length() == 1? temp+'a': temp;
        sort[p]=temp;

    }

    int rez[3] = {
        abs(GetLetterPos(sort[0][1])-GetLetterPos(sort[0][0])),
        abs(GetLetterPos(sort[1][1])-GetLetterPos(sort[1][0])),
        abs(GetLetterPos(sort[2][1])-GetLetterPos(sort[2][0]))
    };
    sum = rez[1]+rez[0]+rez[2];
    return sum==ALPHA;
}
template<int size>
bool DecompleKey::CheckLetter(char* mav, char letter)
{
    bool check = false;
    for (int i = 0; i < size; i++)
    {
        check = (mav[i] == letter);
        if (check) {return true;}
    }
    return check;
}

int DecompleKey::GetLetterPos(char letter)
{
    int count= 0;
    for(int i =0; i < 26; i++)
    {
        if (letter == alphabet[i]){return count;}
        count++;
    }
    return -1;
}
