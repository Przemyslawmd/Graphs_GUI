
#ifndef GUI_GRAPHS_NODE_H
#define GUI_GRAPHS_NODE_H

#include <time.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "defines.h"
#include "services/font.h"


constexpr size_t INITIAL_NODE_X = 30;
constexpr size_t INITIAL_NODE_Y = 60;
constexpr size_t CIRCLE_POINTS = 100;
constexpr float RADIUS = 20;


struct NodeGui : public sf::Drawable
{
    NodeGui() : circle{ RADIUS, CIRCLE_POINTS }, selected{ false }, text{ FontStore::getFont() } 
    {
        circle.setFillColor({ RED, GREEN, BLUE });
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(14);
        setPosition({ INITIAL_NODE_X, INITIAL_NODE_Y });
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(circle);
        target.draw(text);
    }

    void setPosition(const sf::Vector2f& position)
    {
        circle.setPosition(position);
        text.setPosition({ position.x + 15, position.y + 12 });
    };

    void changeSelect()
    {
        if (!selected) {
            circle.setOutlineColor(sf::Color::Black);
            circle.setOutlineThickness(3.0f);
            selectTime = time(0);
        } else {
            circle.setOutlineThickness(0.0f);
            selectTime = 0;
        }
        selected = !selected;
    };

    sf::CircleShape circle;
    sf::Text text;
    char key;
    bool selected;
    time_t selectTime;
};

#endif

