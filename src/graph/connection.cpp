
#include "connection.h"

#include "utils.h"
#include "defines.h"
#include "services/font.h"

constexpr size_t LINE_WIDTH = 3;


Connection::Connection(float length, char src, char dst) : line{ sf::Vector2f{ length, LINE_WIDTH }}, 
                                                           srcKey{ src }, dstKey{ dst }, 
                                                           text{ FontStore::getFont() }, 
                                                           arrow{ 10, 100 },
                                                           selected{ false }
{
    line.setFillColor({ RED, GREEN, BLUE });
    line.setOutlineColor(sf::Color::Black);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(14);
    arrow.setFillColor(sf::Color::Green);
    len = length;
};


void Connection::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(line);
    target.draw(text);
    target.draw(arrow);
}

#include <iostream>

void Connection::setCoordinates(const sf::Vector2f& srcPos, const sf::Vector2f& dstPos)
{
    line.setPosition({ srcPos.x + NODE_RADIUS, srcPos.y + NODE_RADIUS });
    float angle = calculateAngle(srcPos, dstPos);
    line.setRotation(sf::degrees(angle));
    sf::FloatRect bound = line.getGlobalBounds();
    text.setPosition({ bound.getCenter().x, bound.getCenter().y - 15 });
    
    //sin = y / size.x;

    //sin = y / x;
    //y = sin * x

    float y = sin(3.14 / 180 *  angle) * line.getSize().x;
    std::cout << line.getSize().x  << std::endl;
    std::cout << "angle " << angle << std::endl;
    std::cout << "sin angle " << sin(3.14159265 / 180.f * angle) << std::endl;
    std::cout << "y " << y << std::endl;
    //y = sin(line.getRotation().asDegrees()) * line.getSize().x;
    //auto b = cos(angle) * line.getSize().x;
    float x = cos(3.14159265 / 180.f * angle) * line.getSize().x;

    //float angle = atan(distance_y / distance_x) * 180 / PI;

    //line.getPosition().x; +line.getSize().x;
    //auto x = bound.position.x;
    //auto y = bound.position.y;
    //auto a = bound.size.x;
    //auto b = bound.size.y;
    arrow.setPosition({ line.getPosition().x + x, line.getPosition().y + y});
    //arrow.setRotation(sf::degrees(angle + 90));
    //arrow.setRotation(sf::degrees(angle));
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

