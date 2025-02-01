
#ifndef GUI_GRAPHS_NODE_H
#define GUI_GRAPHS_NODE_H

#include <SFML/Graphics.hpp>

constexpr size_t CIRCLE_POINTS = 100;


struct Node : public sf::Drawable
{
    Node(float radius, sf::Font& font) : circle{ radius, CIRCLE_POINTS }, isIndicated{ false }, value(font) {}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(circle);
        target.draw(value);
    }

    sf::CircleShape circle;
    sf::Text value;
    size_t index;
    bool isIndicated;
    std::vector<size_t> connections;
};

#endif

