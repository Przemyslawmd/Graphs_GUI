
#ifndef GUI_GRAPHS_CONNECTION_H
#define GUI_GRAPHS_CONNECTION_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "services/font.h"


constexpr size_t LINE_WIDTH = 3;


struct ConnectionLibraryInterface
{
    char src;
    char dst; 
    size_t weight;
};


struct Connection : public sf::Drawable
{
    Connection(float length, char srcKey, char dstKey)
        : line{ sf::Vector2f{ length, LINE_WIDTH }}, srcKey(srcKey), dstKey(dstKey), text(FontStore::getFont()) {};

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
};

#endif

