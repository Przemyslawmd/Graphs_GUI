
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

    void resetKeys();

private:
    const std::array<char, 5> defaultKeys = { 'A', 'B', 'C', 'D', 'E' };
    std::stack<char> keys;
};

#endif

