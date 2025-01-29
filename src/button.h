
#ifndef GUI_GRAPHS_BUTTON_H
#define GUI_GRAPHS_BUTTON_H

#include <SFML/Graphics.hpp>


class Button
{
public:
    Button(float width, float height, sf::Font& font, const std::string& text) : text(font, text, 15), shape({  width, height }) {}

    sf::RectangleShape shape;
    sf::Text text;
};

#endif
