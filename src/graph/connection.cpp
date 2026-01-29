
#include "connection.h"

#include "utils.h"
#include "colors.h"

constexpr size_t LINE_WIDTH = 3;


Connection::Connection(float length, char src, char dst, bool isDirected) : line{ sf::Vector2f{ length, LINE_WIDTH }}, 
                                                                            srcKey{ src }, dstKey{ dst }, 
                                                                            directed{ isDirected }
{
    line.setFillColor({ colors.at(DEFAULT_COL).R, colors.at(DEFAULT_COL).G, colors.at(DEFAULT_COL).B });
    line.setOutlineColor(sf::Color::Black);
    arrow.setFillColor({ colors.at(DEFAULT_COL).R, colors.at(DEFAULT_COL).G, colors.at(DEFAULT_COL).B });
    arrow.setOutlineColor(sf::Color::Black);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(14);
}


void Connection::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(line);
    target.draw(text);
    if (directed) {
        target.draw(arrow);
    }
}


void Connection::setCoordinates(const sf::Vector2f& srcPos, const sf::Vector2f& dstPos)
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


bool Connection::isMatch(char src, char dst) const
{
    if (directed) {
        return src == srcKey && dst == dstKey;
    }
    return (src == srcKey && dst == dstKey) || (src == dstKey && dst == srcKey);
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
    line.setFillColor({ colors.at(DEFAULT_COL).R, colors.at(DEFAULT_COL).G, colors.at(DEFAULT_COL).B });
    if (directed) {
        arrow.setFillColor({ colors.at(DEFAULT_COL).R, colors.at(DEFAULT_COL).G, colors.at(DEFAULT_COL).B });
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

