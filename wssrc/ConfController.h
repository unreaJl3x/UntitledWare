#ifndef CONFCONTROLLER_H
#define CONFCONTROLLER_H

#include <iostream>
#include <windows.h>
#include "thread"
#include "map_and_keys.h"
using namespace std;

class ConfController {
public:
    ConfController() {
        InitKeys();
        date.Add("", Dates());
        date._map[date._keys[0]].dateFov.dateIndf = "FovChanger";
        date._map[date._keys[0]].dateFov.fovValue = value<int>(100,60, "fovValue");
        date._map[date._keys[0]].dateFov.active = false;

        date._map[date._keys[0]].radarHack.dateIndf = "RadarHack";
        date._map[date._keys[0]].radarHack.active = false;
    }

private:
    map_and_keys<int, string> keyList;
private:
    void InitKeys();

    template <typename T>
    class value {
        public:
            T mValue;
            T dValue;
        string key;

            value(T mainValue, T defaultValue, string) {
                this->mValue = mainValue;
                this->dValue = defaultValue;
            }
            value() = default;
    };

    class Date {
    public:
        bool active;
        string dateIndf;
    };
    struct DateFov : Date{
        value<int> fovValue;
    };
    struct Dates {
        DateFov dateFov;
        Date radarHack;
        Date esp;
    };

public:
    void GetKeyDown(string*);

    bool* GetLinkB(string);
    int* GetLinkI(string);
    map_and_keys<string, Dates> date ;//= map_and_keys<string, Dates>(false);
};



#endif //CONFCONTROLLER_H
