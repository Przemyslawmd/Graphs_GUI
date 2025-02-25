
#ifndef GUI_GRAPHS_RADIO_H
#define GUI_GRAPHS_RADIO_H

#include <string>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>


class Radio : public sf::Drawable
{
public:
    Radio(float radius, sf::Font& font, const std::string& title);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::RectangleShape radio;
    sf::Text text;
    bool selected;
};

#endif

