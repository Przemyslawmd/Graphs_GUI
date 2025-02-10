
#include "keys.h"


char Keys::getKey()
{
    char key = keys.top();
    keys.pop();
    return key;
}


void Keys::giveBackKey(char key)
{
    keys.push(key);
}


void Keys::prepareKeys()
{
    auto empty = std::stack<char>();
    keys.swap(empty);
    for (int i = defaultKeys.size() - 1; i >= 0; i--) {
        keys.push(defaultKeys[i]);
    }
}

