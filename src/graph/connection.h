
#ifndef GUI_GRAPHS_CONNECTION_H
#define GUI_GRAPHS_CONNECTION_H

#include <SFML/Graphics.hpp>

constexpr size_t LINE_WIDTH = 3;


struct ConnectionLibraryInterface
{
    char src;
    char dst; 
    size_t weight;
};


struct Connection : public sf::Drawable
{
    Connection(float length, size_t src, size_t dst, char srcKey, char dstKey, sf::Font& font) 
        : line{ sf::Vector2f{ length, LINE_WIDTH }}, src(src), dst(dst), srcKey(srcKey), dstKey(dstKey), text(font) {};

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(line);
        target.draw(text);
    }

    bool isMatch(char node_1, char node_2) const
    {
        return (node_1 == srcKey && node_2 == dstKey) || (node_1 == dstKey && node_2 == srcKey);
    }

    sf::RectangleShape line;
    sf::Text text;
    char srcKey;
    char dstKey;
    size_t src;
    size_t dst;
};

#endif

