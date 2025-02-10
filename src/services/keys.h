
#ifndef GUI_GRAPHS_KEYS_H
#define GUI_GRAPHS_KEYS_H

#include <array>
#include <stack>


class Keys
{
public:
    Keys() = default;

    char getKey();
    void giveBackKey(char);

    void prepareKeys();

private:
    const std::array<char, 30> defaultKeys = 
    { 
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
        'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5'
    };
    std::stack<char> keys;
};

#endif

