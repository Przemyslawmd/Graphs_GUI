
#include "connection.h"

#include "utils.h"
#include "defines.h"
#include "services/font.h"

constexpr size_t LINE_WIDTH = 3;


Connection::Connection(float length, char src, char dst)
    : line{ sf::Vector2f{ length, LINE_WIDTH } }, srcKey{ src }, dstKey{ dst }, text{ FontStore::getFont() }, selected{ false }
{
    line.setFillColor({ RED, GREEN, BLUE });
    line.setOutlineColor(sf::Color::Black);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(14);
};


void Connection::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(line);
    target.draw(text);
}


void Connection::setCoordinates(const sf::Vector2f& srcPos, const sf::Vector2f& dstPos)
{
    line.setPosition({ srcPos.x + NODE_RADIUS, srcPos.y + NODE_RADIUS });
    float angle = calculateAngle(srcPos, dstPos);
    line.setRotation(sf::degrees(angle));
    sf::FloatRect bound = line.getGlobalBounds();
    text.setPosition({ bound.getCenter().x, bound.getCenter().y - 15 });
}


bool Connection::isMatch(char key_1, char key_2) const
{
    return (key_1 == srcKey && key_2 == dstKey) || (key_1 == dstKey && key_2 == srcKey);
}


bool Connection::isColor() const
{
    return line.getFillColor() == sf::Color::Red;
}


void Connection::changeSelect()
{
    if (!selected) {
        line.setOutlineThickness(2.0f);
    }
    else {
        line.setOutlineThickness(0.0f);
    }
    selected = !selected;
}

