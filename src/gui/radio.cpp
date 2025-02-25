
#include "radio.h"


Radio::Radio(float radius, sf::Font& font, const std::string& title) : radio{{ 15, 15 }}, text{ font, title, 14 }, selected { false }
{
    radio.setOutlineColor(sf::Color::Black);
    radio.setOutlineThickness(2);
    text.setFillColor(sf::Color::Black);
}


void Radio::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(radio);
    target.draw(text);
}

