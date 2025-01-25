
#ifndef GUI_GRAPHS_MODEL_H
#define GUI_GRAPHS_MODEL_H

#include <memory>

#include <SFML/Graphics.hpp>


struct Node 
{
    sf::CircleShape shape;
    bool isIndicated;
};


class Model
{
public:
    Model() = default;

    void createNode(float radius);
    std::vector<Node>& getNodes();

    void createConnection();
    std::vector<sf::RectangleShape>& getConnections();

private:
    std::vector<Node> nodes;
    std::vector<sf::RectangleShape> connections;
};

#endif 

