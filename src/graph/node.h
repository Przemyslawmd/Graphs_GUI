
#ifndef GUI_GRAPHS_NODE_H
#define GUI_GRAPHS_NODE_H

#include <SFML/Graphics.hpp>

constexpr size_t CIRCLE_POINTS = 100;
constexpr float RADIUS = 20;


struct Node : public sf::Drawable
{
    Node(sf::Font& font) : circle{ RADIUS, CIRCLE_POINTS }, isIndicated{ false }, value(font) {}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(circle);
        target.draw(value);
    }

    void setPosition(const sf::Vector2f& position)
    {
        circle.setPosition(position);
        value.setPosition({ position.x + 15, position.y + 12 });
    };

    sf::CircleShape circle;
    sf::Text value;
    bool isIndicated;
    std::vector<size_t> connections;
};

#endif

