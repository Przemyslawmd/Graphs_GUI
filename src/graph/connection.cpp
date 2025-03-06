
#include "connection.h"

#include "utils.h"
#include "defines.h"
#include "services/font.h"

constexpr size_t LINE_WIDTH = 3;
constexpr size_t ARROW_RADIUS = 10;


Connection::Connection(float length, char src, char dst, bool isDirected) : line{ sf::Vector2f{ length, LINE_WIDTH }}, 
                                                                            srcKey{ src }, dstKey{ dst }, 
                                                                            text{ FontStore::getFont() }, 
                                                                            arrow{ ARROW_RADIUS, 3 },
                                                                            selected{ false },
                                                                            directed{ isDirected }
{
    line.setFillColor({ RED, GREEN, BLUE });
    line.setOutlineColor(sf::Color::Black);
    arrow.setFillColor({ RED, GREEN, BLUE });
    arrow.setOutlineColor(sf::Color::Black);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(14);
};


void Connection::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(line);
    target.draw(text);
    if (directed) {
        target.draw(arrow);
    }
}


void Connection::setCoordinates(sf::Vector2f& srcPos, sf::Vector2f& dstPos)
{
    line.setPosition({ srcPos.x + NODE_RADIUS, srcPos.y + NODE_RADIUS });
    float angle = calculateAngle(srcPos, dstPos);
    line.setRotation(sf::degrees(angle));
    sf::FloatRect bound = line.getGlobalBounds();
    text.setPosition({ bound.getCenter().x, bound.getCenter().y - 15 });

    if (!directed) {
        return;
    }

    float length = calculateConnectionLength(srcPos, dstPos);
    float sine = getSine(angle);
    float cosine = getCosine(angle);

    float sizeY = sine * (length - 22);
    float sizeX = cosine * (length - 22);
    float arrowPosX = line.getPosition().x + sizeX + sine * (ARROW_RADIUS - 1);
    float arrowPosY = line.getPosition().y + sizeY - cosine * (ARROW_RADIUS - 1);

    arrow.setPosition({ arrowPosX, arrowPosY });
    arrow.setRotation(sf::degrees(angle + 90));
}


void Connection::setSize(float length)
{
    line.setSize({ length, LINE_WIDTH });
}


bool Connection::isMatch(char key_1, char key_2) const
{
    return (key_1 == srcKey && key_2 == dstKey) || (key_1 == dstKey && key_2 == srcKey);
}


void Connection::colorConnection()
{
    line.setFillColor(sf::Color::Red);
    if (directed) {
        arrow.setFillColor(sf::Color::Red);
    }
}


void Connection::resetColor()
{
    line.setFillColor({ RED, GREEN, BLUE });
    if (directed) {
        arrow.setFillColor({ RED, GREEN, BLUE });
    }
}


bool Connection::isColor() const
{
    return line.getFillColor() == sf::Color::Red;
}


void Connection::changeSelect()
{
    if (!selected) {
        line.setOutlineThickness(2.0f);
        arrow.setOutlineThickness(2.0f);
    }
    else {
        line.setOutlineThickness(0.0f);
        arrow.setOutlineThickness(0.0f);
    }
    selected = !selected;
}

