
#include "input.h"


constexpr char VERTICAL_BAR = '|';


Input::Input(float width, float height, sf::Font& font) : text(font), shape({ width, height }), vertical(font, VERTICAL_BAR)
{
    shape.setFillColor(sf::Color::White);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);
    text.setCharacterSize(13);
    text.setFillColor(sf::Color::Black);
    vertical.setCharacterSize(13);
    vertical.setFillColor(sf::Color::Black);
    verticalCounter = 0;
    focus = false;
}


void Input::checkFocus()
{
    if (!focus) {
        return;
    }
    if (++verticalCounter == 60) {
        verticalCounter = 0;
    }
}


void Input::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape);
    target.draw(text);
    if (focus && verticalCounter >= 30 && verticalCounter <= 60) {
        target.draw(vertical);
    }
}


void Input::updateText(const char letter)
{
    auto& str = text.getString();
    if (letter == '\b') {
        text.setString(str.substring(0, str.getSize() - 1));
    } 
    else {
        text.setString(str + letter);
    }
    auto lastCharPos = text.findCharacterPos(str.getSize() - 1);
    vertical.setPosition({ lastCharPos.x + 7, lastCharPos.y - 2 });
}

