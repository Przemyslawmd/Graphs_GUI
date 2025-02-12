
#ifndef GUI_GRAPHS_NODE_H
#define GUI_GRAPHS_NODE_H

#include <time.h>

#include <SFML/Graphics.hpp>

constexpr size_t CIRCLE_POINTS = 100;
constexpr float RADIUS = 20;


struct NodeGui : public sf::Drawable
{
    NodeGui(sf::Font& font) : circle{ RADIUS, CIRCLE_POINTS }, selected{ false }, text(font) {}

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
        if (selected == false) {
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
    char value;
    bool selected;
    time_t selectTime;
    std::vector<size_t> connections;
};

#endif

