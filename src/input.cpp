
#include "input.h"


Input::Input(float width, float height, sf::Font& font) : text(font), verticalBar(font, '|'), shape({ width, height }), counter(0)
{
    text.setCharacterSize(13);
    verticalBar.setCharacterSize(13);
    verticalBar.setFillColor(sf::Color::Black);
}


void Input::checkInput()
{
    if (++counter == 60) {
        counter = 0;
        return;
    }
    if (counter > 30) {
        verticalBar.setPosition(sf::Vector2f{ text.getPosition().x + 1, text.getPosition().y });
    }
}


void Input::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape);
    target.draw(text);
    if (counter > 30) {
        target.draw(verticalBar);
    }
}

