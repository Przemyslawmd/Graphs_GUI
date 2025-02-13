
#ifndef GUI_GRAPHS_BUTTON_H
#define GUI_GRAPHS_BUTTON_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>


class Button : public sf::Drawable
{
public:
    Button(float width, float height, sf::Font& font, const std::string& text);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::RectangleShape shape;
    sf::Text text;
};

#endif
