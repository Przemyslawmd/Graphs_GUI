
#ifndef GUI_GRAPHS_BUTTON_H
#define GUI_GRAPHS_BUTTON_H

#include <SFML/Graphics.hpp>


class Button : public sf::Drawable
{
public:
    Button(float width, float height, sf::Font& font, const std::string& text) : text(font, text, 15), shape({ width, height }) {}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(shape);
        target.draw(text);
    }

    sf::RectangleShape shape;
    sf::Text text;
};

#endif
