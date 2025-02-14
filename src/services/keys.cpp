
#include "keys.h"

#include <algorithm>


char Keys::getKey()
{
    auto key = std::ranges::find_if(keys, [](const auto& k) { return k.used == false; });
    key->used = true;
    return key->key;
}


void Keys::giveBackKey(char keyToBack)
{
    auto key = std::ranges::find_if(keys, [keyToBack](const auto& k) { return k.used == true && k.key == keyToBack; });
    if (key != keys.end()) {
        key->used = false;
    }
}


void Keys::restoreKeys()
{
    for (auto& key : keys) {
        key.used = false;
    }
}

