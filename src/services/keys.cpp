
#include <algorithm>

#include "keys.h"


char Keys::getKey()
{
    char key = keys.back();
    keys.pop_back();
    return key;
}


void Keys::giveBackKey(char key)
{
    if (std::ranges::none_of(defaultKeys, [key](char k) { return k == key; }) || 
        std::ranges::any_of(keys, [key](char k) { return k == key; })) {
            return;
    }
    keys.push_back(key);
}


void Keys::prepareKeys()
{
    auto empty = std::list<char>();
    keys.swap(empty);
    keys.insert(keys.begin(), std::begin(defaultKeys), std::end(defaultKeys));
    keys.reverse();
}

