
#include "keys.h"


char Keys::getKey()
{
    char key = keys.back();
    keys.pop_back();
    return key;
}


void Keys::giveBackKey(char key)
{
    if (std::find(defaultKeys.begin(), defaultKeys.end(), key) == defaultKeys.end()) {
        return;
    }
    if (std::find(keys.begin(), keys.end(), key) != keys.end()) {
        return;
    }
    keys.push_back(key);
}


void Keys::prepareKeys()
{
    auto empty = std::list<char>();
    keys.swap(empty);
    for (int i = defaultKeys.size() - 1; i >= 0; i--) {
        keys.push_back(defaultKeys[i]);
    }
}

