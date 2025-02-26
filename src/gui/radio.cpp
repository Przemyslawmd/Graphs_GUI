
#include "radio.h"


Radio::Radio(float width, float height, sf::Font& font, const std::string& title) : radio{{ width, height }}, 
                                                                                    text{ font, title, 14 }, 
                                                                                    selected { false }
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


void Radio::changeSelect()
{
    if (!selected) {
        radio.setFillColor({ 00, 0xCC, 00 });
    }
    else {
        radio.setFillColor(sf::Color::White);
    }
    selected = !selected;
}

