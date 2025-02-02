
#ifndef GUI_GRAPHS_CONNECTION_H
#define GUI_GRAPHS_CONNECTION_H

#include <SFML/Graphics.hpp>

constexpr size_t CONNECTION_LINE_WIDTH = 3;


struct Connection : public sf::Drawable
{
    Connection(float length, size_t node_1, size_t node_2) 
        : line{ sf::Vector2f{ length, CONNECTION_LINE_WIDTH }}, node_1(node_1), node_2(node_2) {}; 

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(line);
    }

    sf::RectangleShape line;
    size_t node_1;
    size_t node_2;
};

#endif

