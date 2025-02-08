
#ifndef GUI_GRAPHS_NODE_H
#define GUI_GRAPHS_NODE_H

#include <SFML/Graphics.hpp>

constexpr size_t CIRCLE_POINTS = 100;
constexpr float RADIUS = 20;


struct NodeGui : public sf::Drawable
{
    NodeGui(sf::Font& font) : circle{ RADIUS, CIRCLE_POINTS }, isIndicated{ false }, text(font) {}

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

    sf::CircleShape circle;
    sf::Text text;
    char value;
    bool isIndicated;
    std::vector<size_t> connections;
};

#endif

