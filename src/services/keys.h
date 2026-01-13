
#ifndef GUI_GRAPHS_KEYS_H
#define GUI_GRAPHS_KEYS_H

#include <array>

#include "defines.h"


struct KeyStore
{
    char key;
    bool used;
};


class Keys
{
public:
    Keys() = default;

    char getKey();
    void giveBackKey(char);
    void setKeyAsUsed(char);

    void restoreKeys();

private:
    std::array<KeyStore, MAX_NODES> keys = {{
        { 'A', false }, { 'B', false }, { 'C', false }, { 'D', false }, { 'E', false },
        { 'F', false }, { 'G', false }, { 'H', false }, { 'I', false }, { 'J', false },
        { 'K', false }, { 'L', false }, { 'M', false }, { 'N', false }, { 'O', false },
        { 'P', false }, { 'Q', false }, { 'R', false }, { 'S', false }, { 'T', false },
        { 'V', false }, { 'W', false }, { 'X', false }, { 'Y', false }, { 'Z', false },
        { '1', false }, { '2', false }, { '3', false }, { '4', false }, { '5', false }
    }};
};

#endif

