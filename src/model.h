
#ifndef GUI_GRAPHS_MODEL_H
#define GUI_GRAPHS_MODEL_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "message.h"


constexpr size_t CIRCLE_POINTS = 100;
constexpr size_t CONNECTION_LINE_WIDTH = 3;


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


struct Connection : public sf::Drawable
{
    Connection(float length, size_t node_1, size_t node_2) 
        : line{ sf::Vector2f{ length, CONNECTION_LINE_WIDTH }}, node_1{ node_1 }, node_2{ node_2 } {}; 

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(line);
    }
    
    sf::RectangleShape line;
    size_t node_1;
    size_t node_2;
};


class Model
{
public:
    Model() = default;

    void createNode(float radius, sf::Font&, const std::string&);
    std::vector<Node>& getNodes();

    Message createConnection();
    void moveConnection(size_t index);
    std::vector<Connection>& getConnections();

    void removeAll();

private:
    std::vector<Node> nodes;
    std::vector<Connection> connections;
};

#endif 

