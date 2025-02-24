#ifndef MAP_AND_KEYS_H
#define MAP_AND_KEYS_H

#include <iostream>
#include <map>
#include <vector>
using namespace std;

template <typename typeKey, typename typeValue>
class map_and_keys {
public:
    map<typeKey, typeValue> _map;
    vector<typeKey> _keys;

    typeValue operator [] (typeKey tk) {
        return _map[tk];
    }
    bool Add(typeKey key, typeValue value) {
        for (typeKey k : _keys) {
            if (k==key) { return false; }
        }
        _map[key]=value;
        _keys.push_back(key);
        return true;
    }
    bool Remove(string removeKey) {
        if (_keys.size() == 0) { return false; }
        for (int key = 0; key < _keys.size(); key++) {
            if (_keys[key] == removeKey) {
                _map.erase(removeKey);
                _keys.erase(_keys.begin()+key);
                return true;
            }
        }
        return false;
    }
    bool Set(typeKey keyType, typeValue value) {
        for(string key : _keys) {
            if (key == keyType) {
                _map[key] = value;
                return true;
            }
        }
        return false;
    };
    bool IsNull() { return _keys.size()==0; }
};
#endif //MAP_AND_KEYS_H