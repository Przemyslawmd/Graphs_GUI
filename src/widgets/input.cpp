
#include "input.h"


constexpr char VERTICAL_BAR = '|';


Input::Input(float width, float height, sf::Font& font) : text(font), shape({ width, height }), counter(0), focus(false)
{
    shape.setFillColor(sf::Color::White);
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Black);
    text.setCharacterSize(13);
    text.setFillColor(sf::Color::Black);
}


void Input::checkFocus()
{
    if (!focus) {
        return;
    }
    if (++counter == 60) {
        auto& str = text.getString();
        text.setString(str.substring(0, str.getSize() - 1));
        counter = 0;
        return;
    }
    if (counter == 30) {
        text.setString(text.getString() + VERTICAL_BAR);
    }
}


void Input::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape);
    target.draw(text);
}

