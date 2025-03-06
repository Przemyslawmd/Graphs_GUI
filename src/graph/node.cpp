
#include "node.h"

#include "defines.h"
#include "services/font.h"

constexpr size_t INITIAL_NODE_X = 30;
constexpr size_t INITIAL_NODE_Y = 75;
constexpr size_t CIRCLE_POINTS = 100;


NodeGui::NodeGui(char key) : circle{ NODE_RADIUS, 100 }, selected{ false }, text{ FontStore::getFont() }, key{ key }
{
    circle.setFillColor({ RED, GREEN, BLUE });
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(14);
    setPosition({ INITIAL_NODE_X, INITIAL_NODE_Y });
    text.setString(key);
}


void NodeGui::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(circle);
    target.draw(text);
}


void NodeGui::setPosition(const sf::Vector2f& position)
{
    circle.setPosition(position);
    text.setPosition({ position.x + 15, position.y + 12 });
};


float NodeGui::getPositionX() const
{
    return circle.getPosition().x;
}


float NodeGui::getPositionY() const
{
    return circle.getPosition().y;
}


void NodeGui::changeSelect()
{
    if (!selected) {
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(3.0f);
        selectTime = time(0);
    }
    else {
        circle.setOutlineThickness(0.0f);
        selectTime = 0;
    }
    selected = !selected;
};

