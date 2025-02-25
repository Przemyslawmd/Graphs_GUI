
#include "radio.h"


Radio::Radio(float radius, sf::Font& font, const std::string& title) : text(font, title, 14) {}


void Radio::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(circle);
}

