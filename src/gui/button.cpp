
#include "button.h"


Button::Button(float width, float height, sf::Font& font, const std::string& text_) : text(font, text_, 14), shape({ width, height })
{
    shape.setFillColor({ 223, 243, 246 });
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);
    text.setFillColor(sf::Color::Black);
}


void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape);
    target.draw(text);
}

